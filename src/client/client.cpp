#include "client.h"
#include "sdl/window.h"
#include "sdl/game_scene.h"
#include "position.h"
#include "communication/client_protocol.h"
#include "communication/action_thread.h"
#include "../common/src/packet.h"
#include "../common/src/chess_exception.h"
#include "../common/src/client_data.h"
#include "sdl/event_handler_thread.h"
#include "sdl/sound/sound_handler.h"
#include "login/login_handler_thread.h"
#include "sdl/login_scene.h"
#include "login/login_state_handler.h"
#include "game/chat.h"
#include "game/chess_log.h"
#include "game/error_log.h"
#include "game/turn_log.h"
#include <SDL2pp/Mixer.hh>
#include <iostream>
#include <sstream>
#include <memory>

#define FRAME_RATE 60
#define FONT_SIZE 10
#define MAX_CHAR_ENTRY 29

void Client::gameRenderLoop(GameScene &scene, Game &game, TextEntry &text_entry,
                            HandlerThread &handler, Renderer &renderer) {
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

    if (frame_delta < 1000 / FRAME_RATE)
      SDL_Delay(1000 / FRAME_RATE);
  }
}

void Client::loginRenderLoop(LoginScene &login_renderer,
                             HandlerThread &login_handler,
                             Renderer &renderer) {
  while (login_handler.isOpen()) {
    // Timing: calculate difference between this and previous frame
    // in milliseconds
    uint32_t before_render_ticks = SDL_GetTicks();

    // Show rendered frame
    renderer.render(login_renderer);

    uint32_t after_render_ticks = SDL_GetTicks();
    uint32_t frame_delta = after_render_ticks - before_render_ticks;

    // Frame limiter: sleep for a little bit to not eat 100% of CPU
    if (frame_delta < 1000 / FRAME_RATE)
      SDL_Delay(1000 / FRAME_RATE);
  }
}

// TODO modularizar
void Client::execute() {
  Window window;
  Renderer &renderer = window.renderer();
  Font font(FONT_SIZE);
  ButtonSpriteRepository button_sprite_repository(renderer);
  TextSpriteRepository text_sprite_repository(renderer, font);
  Login login;
  LoginStateHandler login_state_handler(login, button_sprite_repository,
                                        text_sprite_repository);
  LoginScene login_scene(window, login_state_handler);
  LoginHandlerThread login_handler(login, login_state_handler);

  login_handler.start();
  loginRenderLoop(login_scene, login_handler, renderer);
  login_handler.join();

  if (login_handler.was_closed())
    return;

  // if we are here the client is connected to a match
  Socket socket = login.getClientSocket();
  role = login.getRole();
  RemoteClientSender sender_thread(socket, send);
  RemoteClientReceiver receiver_thread(socket, received);

  Game game(window, send, role, font);
  GameScene scene(window, game.getBoard(), font, text_sprite_repository,
                  button_sprite_repository);
  Chat chat(send, scene);
  ChessLog chess_log(scene);
  ErrorLog error_log(scene);
  TurnLog turn_log(scene);
  TextEntry text_entry(scene.getChatWidth() / font.size());

  ActionThread action_thread(received, game, chat, chess_log, error_log,
                             turn_log);
  EventHandlerThread event_handler(window, game, chat, text_entry);

  receiver_thread.start();
  sender_thread.start();
  action_thread.start();
  event_handler.start();
  // comment if you dont want to go crazy while debugging.
  //sound_handler.playMusic();

  gameRenderLoop(scene, game, text_entry, event_handler, renderer);

  received.close();
  send.close();
  receiver_thread.notifySocketClosed();
  socket.shutdownAndClose();
  action_thread.join();
  event_handler.join();
  sender_thread.join();
  receiver_thread.join();
}




