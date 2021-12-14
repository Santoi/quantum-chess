#ifndef QUANTUM_CHESS_PROJ_CLIENT_H
#define QUANTUM_CHESS_PROJ_CLIENT_H

#include "game/game.h"
#include "communication/remote_clients_threads.h"
#include "../common/socket.h"
#include "../common/blocking_queue.h"
#include "game/game.h"
#include "communication/remote_client_instructions.h"
#include "sdl/handler_thread.h"
#include "logic/text_entry.h"
#include "sdl/login_scene.h"
#include "sdl/game_scene.h"
#include <string>

class GameScene;

class LoginScene;

class Client {
private:
  ClientData::Role role;

  void gameRenderLoop(GameScene &scene, Game &game, const TextEntry &text_entry,
                      HandlerThread &handler, Renderer &renderer,
                      uint8_t frame_rate);

  void loginRenderLoop(LoginScene &login_renderer,
                       HandlerThread &login_handler, Renderer &renderer,
                       uint8_t frame_rate);

  void handleFirstLogin(Login& login,
                        ButtonSpriteRepository& button_sprite_repository,
                        TextSpriteRepository& text_sprite_repository,
                        Window& window,
                        Renderer& renderer,
                        uint8_t frame_rate, bool& login_was_closed);

  void handleGame(Socket&& socket,
                  ButtonSpriteRepository& button_sprite_repository,
                  TextSpriteRepository& text_sprite_repository, Window& window,
                  Renderer& renderer, Font& font, uint8_t frame_rate,
                  bool& game_quitted);

  void handleSelectAnotherMatchOrQuit(Login& login,
                             ButtonSpriteRepository& button_sprite_repository,
                             TextSpriteRepository& text_sprite_repository,
                             Window& window, Renderer& renderer,
                             uint8_t frame_rate, bool& keep_playing,
                             bool& login_was_closed);

public:
  Client();

  // Execute client login and game.
  // Executes the client threads, such as the receiver, sender, action,
  // event handler and drawer (the main one)
  void execute();

  ~Client() = default;
};

#endif //QUANTUM_CHESS_PROJ_CLIENT_H
