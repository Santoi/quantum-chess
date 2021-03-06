#include "client.h"
#include "sdl/window.h"
#include "sdl/game_scene.h"
#include "game/board_position.h"
#include "communication/client_protocol.h"
#include "communication/action_thread.h"
#include "../common/packet.h"
#include "../common/chess_exception.h"
#include "../common/client_data.h"
#include "sdl/event_handler_thread.h"
#include "sdl/sound_handler.h"
#include "login/login_handler_thread.h"
#include "sdl/login_scene.h"
#include "login/login_state_handler.h"
#include "game/chat.h"
#include "game/chess_log.h"
#include "game/error_log.h"
#include "game/turn_log.h"
#include "config_file.h"
#include "sdl/screen_handler.h"
#include <SDL2pp/Mixer.hh>
#include <iostream>
#include <sstream>
#include <memory>

#define FONT_SIZE 10
#define MAX_CHAR_ENTRY 29
#define CONFIG_PATH "config_files/client_config.txt"

Client::Client() : role(ClientData::ROLE_SPECTATOR) {}

void Client::gameRenderLoop(GameScene &scene, Game &game,
                            const TextEntry &text_entry,
                            HandlerThread &handler, Renderer &renderer,
                            uint8_t frame_rate) {
  if (frame_rate == 0)
    frame_rate = 10;
  while (handler.isOpen()) {
    // Timing: calculate difference between this and previous frame
    // in milliseconds
    uint32_t before_render_ticks = SDL_GetTicks();

    // Update chess dimensions to game
    game.setScale(scene.getChessWidth(), scene.getChessHeight());

    // Get current message
    scene.addCurrentMessage(text_entry.getText());

    // Show rendered frame
    renderer.render(scene);

    uint32_t after_render_ticks = SDL_GetTicks();
    uint32_t frame_delta = after_render_ticks - before_render_ticks;

    if (frame_delta < 1000 / frame_rate)
      SDL_Delay(1000 / frame_rate);
  }
}

void Client::loginRenderLoop(LoginScene &login_renderer,
                             HandlerThread &login_handler, Renderer &renderer,
                             uint8_t frame_rate) {
  if (frame_rate == 0)
    frame_rate = 10;
  while (login_handler.isOpen()) {
    // Timing: calculate difference between this and previous frame
    // in milliseconds
    uint32_t before_render_ticks = SDL_GetTicks();

    // Show rendered frame
    renderer.render(login_renderer);

    uint32_t after_render_ticks = SDL_GetTicks();
    uint32_t frame_delta = after_render_ticks - before_render_ticks;

    // Frame limiter: sleep for a little bit to not eat 100% of CPU
    if (frame_delta < 1000 / frame_rate)
      SDL_Delay(1000 / frame_rate);
  }
}

void Client::execute() {
  std::ifstream config_file(CONFIG_PATH);
  ConfigFile config(config_file);
  Window window(std::stoi(config.getValue("res_width")),
                std::stoi(config.getValue("res_height")));
  uint8_t frame_rate = std::stoi(config.getValue("frame_rate"));
  Renderer &renderer = window.renderer();
  Font font(FONT_SIZE);
  ButtonSpriteRepository button_sprite_repository(renderer);
  TextSpriteRepository text_sprite_repository(renderer, font);
  Login login;

  if (!executeLogin(window, login, button_sprite_repository,
                    text_sprite_repository, frame_rate))
    return;

  // if we are here the client is connected to a match
  Socket socket = login.getClientSocket();
  role = login.getRole();

  CoordinateTransformer coordinate_transformer;
  Game game(window, send, role, font, coordinate_transformer);
  executeGame(window, game, socket, coordinate_transformer,
              font, button_sprite_repository,
              text_sprite_repository, frame_rate);
}

void Client::executeGame(Window &window, Game &game, Socket &socket,
                         CoordinateTransformer &coordinate_transformer,
                         Font &font,
                         ButtonSpriteRepository &button_sprite_repository,
                         TextSpriteRepository &text_sprite_repository,
                         uint8_t frame_rate) {
  ScreenHandler screen_handler(role == ClientData::ROLE_SPECTATOR);
  GameScene scene(window, game.getBoard(), font, screen_handler,
                  text_sprite_repository,button_sprite_repository,
                  coordinate_transformer);
  Chat chat(send, scene);
  ChessLog chess_log(scene);
  ErrorLog error_log(scene);
  TurnLog turn_log(scene);
  TextEntry text_entry(scene.getChatWidth() / font.size());

  RemoteClientSender sender_thread(socket, send);
  RemoteClientReceiver receiver_thread(socket, received);
  ActionThread action_thread(received, game, chat, chess_log, error_log,
                             turn_log);
  EventHandlerThread event_handler(window, game,screen_handler,
                                   chat, text_entry);

  receiver_thread.start();
  sender_thread.start();
  action_thread.start();
  event_handler.start();
  // comment if you don't want to go crazy while debugging.
  //sound_handler.playMusic();

  gameRenderLoop(scene, game, text_entry, event_handler, window.renderer(),
                 frame_rate);

  received.close();
  send.close();
  receiver_thread.notifySocketClosed();
  socket.shutdownAndClose();
  action_thread.join();
  event_handler.join();
  sender_thread.join();
  receiver_thread.join();
}

bool Client::executeLogin(Window &window, Login &login,
                          ButtonSpriteRepository &button_sprite_repository,
                          TextSpriteRepository &text_sprite_repository,
                          uint8_t frame_rate) {
  LoginStateHandler login_state_handler(login, button_sprite_repository,
                                        text_sprite_repository);
  LoginScene login_scene(window, login_state_handler);
  LoginHandlerThread login_handler(login, login_state_handler);

  login_handler.start();
  loginRenderLoop(login_scene, login_handler, window.renderer(), frame_rate);
  login_handler.join();

  return !login_handler.was_closed();
}
