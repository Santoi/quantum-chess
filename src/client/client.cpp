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

uint16_t Client::getMatchesInfo(Socket &client_socket) {
  ClientProtocol protocol;
  std::map<uint16_t, std::vector<ClientData>> data =
      protocol.receiveMatchesInfo(client_socket);
  std::cout << "Selecciona de las partidas disponibles a cuál de estas"
               " quieres entrar." << std::endl;
  std::cout << "Las partidas disponibles son" << std::endl;
  uint16_t last_id = 0;
  for (auto it = data.begin(); it != data.end(); ++it) {
    std::cout << "#" << it->first << ": ";
    std::vector<ClientData> &client_data = it->second;
    for (auto it_match = client_data.begin();
         it_match != client_data.end(); ++it_match) {
      char other_cliente_role = ' ';
      switch (it_match->role) {
        case ClientData::ROLE_WHITE:
          other_cliente_role = 'w';
          break;
        case ClientData::ROLE_BLACK:
          other_cliente_role = 'b';
          break;
        case ClientData::ROLE_SPECTATOR:
          other_cliente_role = 'o';
          break;
      }
      std::cout << it_match->name << "#" << it_match->id << "("
                << other_cliente_role << "), ";
    }
    std::cout << std::endl;
    last_id = it->first;
  }
  std::cout << "¿Quieres crear una nueva partida? Escribe entonces "
            << data.size() << std::endl;
  std::cout << "Escriba un número de partida: " << std::endl;
  return last_id;
}

void Client::askPlayerForMatchNumber(Socket &socket, uint16_t first_empty_id) {
  uint16_t game_number;
  std::cin >> game_number;
  ClientProtocol protocol;
  protocol.sendChosenGame(socket, game_number);
  std::string aux;
  std::getline(std::cin, aux); //empty cin buffer
}

std::list<ClientData::Role> Client::getAvailableRoles(Socket &socket) {
  std::list<ClientData::Role> available_roles;
  ClientProtocol protocol;
  protocol.getAvailableRoles(socket, available_roles);
  return available_roles;
}

void Client::associateClientWithARunningMatch(Socket &socket) {
  uint16_t first_empty_id = this->getMatchesInfo(socket) + 1;
  askPlayerForMatchNumber(socket, first_empty_id);
}

void Client::welcomeClientAndAskForNickName() {
  std::cout << "Bienvenido a Quantum Chess. Por favor, ingresá tu nombre para "
               "comenzar a jugar." << std::endl;
  std::cin >> client_nick_name;
  std::cout << "¡Qué tal, " << this->client_nick_name << "! ¿Listo para jugar?"
            << std::endl;
}

void Client::setUpClientsDataInServer(Socket &socket) {
  this->associateClientWithARunningMatch(socket);
  ClientProtocol protocol;
  protocol.sendClientsNickName(socket, this->client_nick_name);
  std::list<ClientData::Role> available_roles = getAvailableRoles(socket);
  // TODO, ahora agarra el primero que haya
  role = *available_roles.begin();
  protocol.sendChosenRole(socket, *available_roles.begin());
}


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


void Client::execute() {
  // welcomeClientAndAskForNickName();
  // Socket socket = Socket::createAConnectedSocket(host, port);

  Window window;
  Renderer &renderer = window.renderer();
  Font font(FONT_SIZE);
  ButtonSpriteRepository button_sprite_repository(renderer);
  TextSpriteRepository text_sprite_repository(renderer, font);
  Login login;
  LoginStateHandler login_state_handler(login, button_sprite_repository,
                                        text_sprite_repository);
  LoginScene login_scene(login_state_handler, window);
  LoginHandlerThread login_handler(login, login_state_handler);

  login_handler.start();
  loginRenderLoop(login_scene, login_handler, renderer);
  login_handler.join();

  if (login_handler.was_closed())
    return;


  // if we are here the client is connected to a match
  Socket socket = login.getClientSocket();
  client_nick_name = login.getClientNickName();//TODO borrar

  RemoteClientSender sender_thread(socket, send);
  RemoteClientReceiver receiver_thread(socket, received);
  setUpClientsDataInServer(socket);

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

bool Client::readCommand() {
  std::string line;
  std::string op;
  std::getline(std::cin, line);
  std::istringstream iss(line);

  iss >> op;
  if (op == "q" || op == "Q")
    return true;

  if (op == "c") {
    std::string message, temp_message;
    while (!iss.eof()) {
      iss >> temp_message;
      message += temp_message + " ";
    }
    send.push(std::make_shared<RemoteClientChatInstruction>(
        message));

  }

  if (op == "m" || op == "M") {
    int y1 = 0, y2 = 0;
    char x1 = 0, x2 = 0;
    iss >> x1 >> y1 >> x2 >> y2;
    if (x1 < 'A' || x1 > 'H' || x2 < 'A' || x2 > 'H')
      throw ChessException("posicion invalida");

    send.push(std::make_shared<RemoteClientMoveInstruction>(
        Position((uint8_t) x1 - 'A', (uint8_t) y1),
        Position((uint8_t) x2 - 'A', (uint8_t) y2)));
  }
  return false;
}




