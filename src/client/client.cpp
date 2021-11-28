#include <iostream>
#include <sstream>
#include <memory>
#include "client.h"
#include "position.h"
#include "communication/client_protocol.h"
#include "communication/action_thread.h"
#include "../server/src/quantum_chess/chess_exception.h"
#include "../common/src/client_data.h"
#include "sdl/window.h"
#include "sdl/event_handler_thread.h"
#include <SDL2pp/Mixer.hh>
#include "sdl/sound/sound_handler.h"
#include "sdl/login_handler_thread.h"
#include "sdl/login_renderer.h"
#include "sdl/login.h"

#define FRAME_RATE 60

uint16_t Client::getMatchesInfo(Socket &client_socket) {
  ClientProtocol protocol;
  std::map<uint16_t, std::vector<ClientData>> data = std::move(
          protocol.receiveMatchesInfo(client_socket));
  std::cout << "Selecciona de las partidas disponibles a cuál de estas"
               " quieres entrar." << std::endl;
  std::cout << "Las partidas disponibles son" << std::endl;
  uint16_t last_id = 0;
  for (auto it = data.begin(); it != data.end(); ++it) {
    std::cout << "#" << it->first << ": ";
    std::vector<ClientData> &client_data = it->second;
    for (auto it_match = client_data.begin();
         it_match != client_data.end(); ++it_match) {
      char role = ' ';
      switch (it_match->role) {
        case ClientData::ROLE_WHITE:
          role = 'w';
          break;
        case ClientData::ROLE_BLACK:
          role = 'b';
          break;
        case ClientData::ROLE_SPECTATOR:
          role = 'o';
          break;
      }
      std::cout << it_match->name << "#" << it_match->id << "("
                << role << "), ";
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


void doRenderingLoopForSceneWithHandler(Scene* scene, HandlerThread& handler,
                                        Renderer& renderer) {
    while (handler.isOpen()) {
        // Timing: calculate difference between this and previous frame
        // in milliseconds
        uint32_t before_render_ticks = SDL_GetTicks();

        // Show rendered frame
        renderer.render(scene);

        uint32_t after_render_ticks = SDL_GetTicks();
        uint32_t frame_delta = after_render_ticks - before_render_ticks;

        // Frame limiter: sleep for a little bit to not eat 100% of CPU
        if (frame_delta < 1000 / FRAME_RATE)
            SDL_Delay(1000 / FRAME_RATE);
    }
}

void Client::execute(const char *host, const char *port,
                     bool single_threaded_client) {
  SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  SDL2pp::Mixer mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
  SoundHandler sound_handler(mixer);
  sound_handler.playMusic();
  Window window;
  Renderer &renderer = window.renderer();
  LoginRenderer login_renderer(window);
  Login login(window);
  LoginHandlerThread login_handler(login);
  login_handler.start();
  doRenderingLoopForSceneWithHandler(&login_renderer, login_handler, renderer);

  //if we are here the client is connected to a match
  Socket socket = login.getClientSocket();
  client_nick_name = login.getClientNickName();
    /*
     BlockingQueue<std::string> queue;
    Login login(queue);
    LoginHandlerThread login_thread(login);
    login_thread.start();

    std::shared_ptr<std::string> string_ptr;
    queue.pop(string_ptr);
    IP = string_ptr->stoi();
    queue.pop(string_ptr);
    PORT = string_ptr->stoi();
    queue.pop(string_ptr);
    client_nick_name = *string_ptr;
    queue.pop(string_ptr);
    MATCH_NUMBER = string_PTR->stoi();
    welcomeClientAndAskForNickName();
     */
  login_handler.join();

  RemoteClientSender sender_thread(socket, send);
  RemoteClientReceiver receiver_thread(socket, received);
  setUpClientsDataInServer(socket);

  Game game(window, send, role, sound_handler);

  ActionThread action_thread(received, game);
  EventHandlerThread event_handler(game);

  receiver_thread.start();
  sender_thread.start();
  action_thread.start();
  event_handler.start();

  doRenderingLoopForSceneWithHandler(&game, event_handler, renderer);

  received.close();
  send.close();
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
    send.push(std::make_shared<RemoteClientChatInstruction>(client_nick_name,
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




