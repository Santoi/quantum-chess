#include <iostream>
#include <sstream>
#include "client.h"
#include "position.h"
#include "communication/client_protocol.h"
#include "communication/action_thread.h"
#include "../server/src/quantum_chess/chess_exception.h"
#include "../common/src/client_data.h"
#include "sdl/window.h"
#include "sdl/event_handler_thread.h"

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
      char playing = (it_match->isPlayer()) ? 'p' : 'o';
      std::cout << it_match->getName() << "#" << it_match->getId() << "("
                << playing << "), ";
    }
    std::cout << std::endl;
    last_id = it->first;
  }
  std::cout << "¿Quieres crear una nueva partida? Escribe entonces "
            << data.size() << std::endl;
  std::cout << "Escriba un número de partida: " << std::endl;
  return last_id;
}

void Client::askForMatchNumber(Socket &socket, uint16_t first_empty_id) {
  uint16_t game_number;
  std::cin >> game_number;
  ClientProtocol protocol;
  protocol.sendChosenGame(socket, game_number);
  std::string aux;
  std::getline(std::cin, aux); //empty cin buffer
}

void Client::associateClientWithARunningMatch(Socket &socket) {
  uint16_t first_empty_id = this->getMatchesInfo(socket) + 1;
  askForMatchNumber(socket, first_empty_id);
}

void Client::welcomeClientAndAskForNickName() {
  std::cout << "Bienvenido a Quantum Chess. Por favor, ingresá tu nombre para "
               "comenzar a jugar." << std::endl;
  std::cin >> clients_nick_name;
  std::cout << "¡Qué tal, " << this->clients_nick_name << "! ¿Listo para jugar?"
            << std::endl;
}

void Client::setUpClientsDataInServer(Socket &socket) {
  this->associateClientWithARunningMatch(socket);
  ClientProtocol protocol;
  protocol.sendClientsNickName(socket, this->clients_nick_name);
}


void Client::execute(const char *host, const char *port,
                     bool single_threaded_client) {
  SDL2pp::SDL sdl(SDL_INIT_VIDEO);

  welcomeClientAndAskForNickName();
  Socket socket = Socket::createAConnectedSocket(host, port);

  RemoteClientSender sender_thread(socket, send);
  RemoteClientReceiver receiver_thread(socket, received);
  setUpClientsDataInServer(socket);
  
  Window window;
  Renderer &renderer = window.renderer();
  Game game(window, send);

  ActionThread action_thread(received, game);
  EventHandlerThread event_handler(game);

  receiver_thread.start();
  sender_thread.start();
  action_thread.start();
  event_handler.start();

  while (event_handler.isOpen()) {
    unsigned int prev_ticks = SDL_GetTicks();
    // Timing: calculate difference between this and previous frame
    // in milliseconds
    unsigned int frame_ticks = SDL_GetTicks();
    unsigned int frame_delta = frame_ticks - prev_ticks;
    prev_ticks = frame_ticks;

    // Show rendered frame
    renderer.render(game);

    // Frame limiter: sleep for a little bit to not eat 100% of CPU
    SDL_Delay(1);
  }

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
    send.push(std::make_shared<RemoteClientChatInstruction>(clients_nick_name,
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