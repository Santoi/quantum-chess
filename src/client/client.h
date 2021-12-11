#ifndef QUANTUM_CHESS_PROJ_CLIENT_H
#define QUANTUM_CHESS_PROJ_CLIENT_H

#include "game/game.h"
#include "communication/remote_clients_threads.h"
#include "../common/src/socket.h"
#include "../common/src/blocking_queue.h"
#include "game/game.h"
#include "communication/remote_client_instructions.h"
#include "sdl/handler_thread.h"
#include "sdl/chat/text_entry.h"
#include "sdl/login_scene.h"
#include "sdl/game_scene.h"
#include <string>

class GameScene;

class LoginScene;

class Client {
private:
  BlockingQueue<RemoteClientInstruction> received;
  BlockingQueue<RemoteClientInstruction> send;
  ClientData::Role role;

  void gameRenderLoop(GameScene &scene, Game &game, TextEntry &text_entry,
                      HandlerThread &handler, Renderer &renderer);

  void loginRenderLoop(LoginScene &login_renderer, HandlerThread &login_handler,
                       Renderer &renderer);


public:
  Client() = default;

  //Executes client. To stop execution, type "exit" to stdin. If single_threaded_client is true,
  //then the client is single threaded and the work sequence is: 1. send instruction to server and
  //2. receive instruction from server, until the client decides to exit. If single_threaded_client is
  //false, then both remote_sender and remote_receiver threads are started, and client can receive
  //and send instruction without any synchronization. When the command "exit" is read, both sender and
  //receiver threads are joined and the execution is finished.
  void execute();

  //Se destruye el socket cliente.
  ~Client() = default;
};

#endif //QUANTUM_CHESS_PROJ_CLIENT_H
