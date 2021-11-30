#ifndef QUANTUM_CHESS_PROJ_CLIENT_H
#define QUANTUM_CHESS_PROJ_CLIENT_H

#include "game/game.h"
#include "communication/remote_clients_threads.h"
#include "../common/src/socket.h"
#include "../common/src/blocking_queue.h"
#include "communication/remote_client_instructions.h"
#include <string>

class Client {
private:
  BlockingQueue<RemoteClientInstruction> received;
  BlockingQueue<RemoteClientInstruction> send;
  std::string client_nick_name;
  ClientData::Role role;

public:
  Client() = default;

  //Executes client. To stop execution, type "exit" to stdin. If single_threaded_client is true,
  //then the client is single threaded and the work sequence is: 1. send instruction to server and
  //2. receive instruction from server, until the client decides to exit. If single_threaded_client is
  //false, then both remote_sender and remote_receiver threads are started, and client can receive
  //and send instruction without any synchronization. When the command "exit" is read, both sender and
  //receiver threads are joined and the execution is finished.
  void execute(const char *host, const char *port);

  //Se destruye el socket cliente.
  ~Client() = default;

private:
  //Sets up login data in server: this is, the client's nick name and the match the client wants to
  //play in / watch.
  void setUpClientsDataInServer(Socket &socket);

  //Prints to stdout a welcoming message and asks client to type wanted nick name. It saves the
  //given nick name in the client's nick_name attribute.
  void welcomeClientAndAskForNickName();

  //Prints to stdout the number of available matches, and asks the client if them wants to join an
  //existing match or if them wants to create a new match. The chosen match number is sent to the
  //server.
  void associateClientWithARunningMatch(Socket &socket);

  //Prints the number of available matches.
  uint16_t getMatchesInfo(Socket &client_socket);

  //Asks the client to write to stdin the chosen match.
  void askPlayerForMatchNumber(Socket &socket, uint16_t first_empty_id);

  bool readCommand();

  std::list<ClientData::Role> getAvailableRoles(Socket &socket);
};

#endif //QUANTUM_CHESS_PROJ_CLIENT_H
