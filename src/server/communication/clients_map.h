#ifndef QUANTUM_CHESS_PROJ_CLIENTS_MAP_H
#define QUANTUM_CHESS_PROJ_CLIENTS_MAP_H

#include <map>
#include <mutex>
#include "client_handler.h"
#include "../../common/socket.h"
#include "../../common/client_data.h"
#include <vector>
#include "../../common/blocking_queue.h"

class Instruction;

class ClientHandler;

// Protected class that stores clients handlers and their listening queues.
class ClientsMap {
  std::map<uint16_t, ClientHandler> clients;
  std::map<uint16_t, BlockingQueue<Instruction>> listening_queues;
  std::mutex mutex;

public:
  ClientsMap();

  // Adds a new client, creating handler and corresponding threads.
  void
  addNewClient(Socket &&socket, BlockingQueue<Instruction> &match_updates,
               ClientData &client_data);

  // Starts client handler threads corresponding to client id.
  void startClient(uint16_t client_id);

  // Deletes client handler corresponding to client id.
  void deleteClient(uint16_t client_id);

  // Pushes an instruction to listening queue of a client.
  void
  pushInstrToClientListeningQueue(uint16_t client_id,
                                  std::shared_ptr<Instruction> &instr_ptr);

  // Pushes an instruction to listening queues of all clients.
  void addInstrToAllListeningQueues(std::shared_ptr<Instruction> &instr_ptr);

  // Returns size of map.
  size_t size();

  // Stops all clients.
  void stopAllClients();

  // Set booleans depending if roles are available or not.
  void getAvailableRoles(bool &white_available, bool &black_available);

  // Returns a vector with data of clients stored.
  void loadWithClientData(std::vector<ClientData> &vector) const;
};


#endif //QUANTUM_CHESS_PROJ_CLIENTS_MAP_H
