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

void Client::handleFirstLogin(Login& login,
                      ButtonSpriteRepository& button_sprite_repository,
                      TextSpriteRepository& text_sprite_repository,
                      Window& window, Renderer& renderer,
                      uint8_t frame_rate, bool& login_was_closed) {
  LoginStateHandler login_state_handler(login, button_sprite_repository,
                                        text_sprite_repository, false);
  LoginScene login_scene(window, login_state_handler);
  LoginHandlerThread login_handler(login, login_state_handler);

  login_handler.start();
  loginRenderLoop(login_scene, login_handler, renderer, frame_rate);
  login_handler.join();
  login_was_closed = login_handler.was_closed();
}

void startThreads(RemoteClientSender& sender_thread,
                  RemoteClientReceiver& receiver_thread,
                  ActionThread& action_thread,
                  EventHandlerThread& event_handler) {
  sender_thread.start();
  receiver_thread.start();
  action_thread.start();
  event_handler.start();
}

void joinThreads(RemoteClientSender& sender_thread,
                 RemoteClientReceiver& receiver_thread,
                 ActionThread& action_thread,
                 EventHandlerThread& event_handler) {
  action_thread.join();
  event_handler.join();
  sender_thread.join();
  receiver_thread.join();
}

void closeBlockingQueues(BlockingQueue<RemoteClientInstruction>& received,
                         BlockingQueue<RemoteClientInstruction>& send) {
  received.close();
  send.close();
}

void Client::handleGame(Socket&& socket,
                        ButtonSpriteRepository& button_sprite_repository,
                        TextSpriteRepository& text_sprite_repository,
                        Window& window,
                        Renderer& renderer, Font& font, uint8_t frame_rate,
                        bool& game_quitted) {
  BlockingQueue<RemoteClientInstruction> received;
  BlockingQueue<RemoteClientInstruction> send;
  RemoteClientSender sender_thread(socket, send);
  RemoteClientReceiver receiver_thread(socket, received);

  CoordinateTransformer coordinate_transformer;
  Game game(window, send, role, font, coordinate_transformer);
  GameScene scene(window, game.getBoard(), font, text_sprite_repository,
                  button_sprite_repository, coordinate_transformer);
  Chat chat(send, scene);
  ChessLog chess_log(scene);
  ErrorLog error_log(scene);
  TurnLog turn_log(scene);
  TextEntry text_entry(scene.getChatWidth() / font.size());

  ActionThread action_thread(received, game, chat, chess_log,
                             error_log, turn_log);
  EventHandlerThread event_handler(window, game, scene, chat, text_entry);

  startThreads(sender_thread, receiver_thread, action_thread, event_handler);

  // comment if you dont want to go crazy while debugging.
  //sound_handler.playMusic();

  gameRenderLoop(scene, game, text_entry, event_handler,
                 renderer, frame_rate);

  closeBlockingQueues(received, send);

  receiver_thread.notifySocketClosed();
  socket.shutdownAndClose();
  joinThreads(sender_thread, receiver_thread, action_thread, event_handler);
  game_quitted = event_handler.clientQuitted();
}

void Client::handleSelectAnotherMatchOrQuit(Login& login,
                               ButtonSpriteRepository& button_sprite_repository,
                               TextSpriteRepository& text_sprite_repository,
                               Window& window, Renderer& renderer,
                               uint8_t frame_rate, bool& keep_playing,
                               bool& login_was_closed) {
  LoginStateHandler login_state_handler(login, button_sprite_repository,
                                        text_sprite_repository, true);
  LoginScene login_scene(window, login_state_handler);
  LoginHandlerThread login_handler(login, login_state_handler);
  login_handler.start();
  loginRenderLoop(login_scene, login_handler, renderer, frame_rate);
  login_handler.join();
  login_was_closed = login_handler.was_closed();
  keep_playing = login_state_handler.continuePlaying();
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
  bool login_was_closed;
  handleFirstLogin(login, button_sprite_repository,
                   text_sprite_repository, window,
                   renderer, frame_rate, login_was_closed);
  if (login_was_closed)
    return;

  bool keep_playing = true;
  while (keep_playing) {
  // if we are here the client is connected to a match.
    Socket socket = login.getClientSocket();
    role = login.getRole();
    bool game_quitted = false;
    handleGame(std::move(socket), button_sprite_repository,
               text_sprite_repository, window, renderer, font,
               frame_rate, game_quitted);
    if (game_quitted)
      return;
    handleSelectAnotherMatchOrQuit(login, button_sprite_repository,
                                   text_sprite_repository, window,
                                   renderer, frame_rate,
                                   keep_playing, login_was_closed);
    if (login_was_closed)
      return;
  }
}
