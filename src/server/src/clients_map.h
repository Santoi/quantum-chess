#ifndef QUANTUM_CHESS_PROJ_CLIENTS_MAP_H
#define QUANTUM_CHESS_PROJ_CLIENTS_MAP_H

#include <map>
#include <mutex>
#include "client_handler.h"
#include "../../common/src/socket.h"
#include "../../common/src/client_data.h"
//#include "instructions/instruction.h"
#include "../../common/src/blocking_queue.h"

class Instruction;

class ClientHandler;

class ClientsMap {
  std::map<uint16_t, ClientHandler> clients;
  std::map<uint16_t, BlockingQueue<Instruction>> listening_queues;
  std::mutex mutex;

public:
  ClientsMap();

  void
  addNewClient(Socket &&socket, BlockingQueue<Instruction> &match_updates,
               ClientData &client_data);

  void startClient(uint16_t client_id);

  void deleteClient(uint16_t client_id);

  void
  addInstrToClientListeningQueue(uint16_t client_id,
                                 std::shared_ptr<Instruction> &instr_ptr);

  void addInstrToAllListeningQueues(std::shared_ptr<Instruction> &instr_ptr);

  size_t size();

  void stopAllClients();

  void getAvailableRoles(bool &white_available, bool &black_available);

  std::vector<const ClientData *> getClientsData() const;
};


#endif //QUANTUM_CHESS_PROJ_CLIENTS_MAP_H
