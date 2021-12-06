#ifndef QUANTUM_CHESS_PROJ_MATCH_H
#define QUANTUM_CHESS_PROJ_MATCH_H

#include <list>
#include "../../common/src/socket.h"
#include "clients_map.h"
#include "../../common/src/blocking_queue.h"
#include "../../common/src/socket.h"
#include "../../common/src/thread.h"
#include "quantum_chess/board.h"
#include "instructions/instruction.h"
#include "client_handler.h"


class Instruction;

class Match : public Thread {
private:
  Board board;
  // TODO estos maps hay que hacerlos protegidos, podria haber race
  // condition si el server manda algo y justo se une alguien.
  ClientsMap clients_map;
  BlockingQueue<Instruction> match_updates_queue;
  std::ifstream &file;

public:
  //Creates a match, creating the ClientDataRepository and the BlockingQueue<Instruction>. The client's vector
  //is also created and set with an initial capacity of BASE_CLIENTS.
  Match(std::ifstream &file_);

  //Moves the other match's thread, clients, listening queues and the thread safe queue to the new
  //match. The new match also copies the number of accepted clients of the other.
  Match(Match &&other);

  //Adds client to list of clients and nick names repository, and calls the client to start.
  void addClientToMatch(Socket &&client_socket, uint16_t client_id);

  //Pops from updates_queue an instruction, and asks this instruction to makeActionAndNotify.
  void checkAndNotifyUpdates();

  //Iterates over the list of clients, asking each one if the respective client is active. If either
  //of them is active, then a true is returned. If neither is active, a false is returned.
  bool hasActiveClients();

  ~Match() = default;

  void stop();

  std::vector<ClientData> getClientsData() const;

  void deleteClientWithId(uint16_t client_id);

  Board &getBoard();

  void addInstrToClientListeningQueue(uint16_t client_id,
                                      std::shared_ptr<Instruction> &instr_ptr);

  void addInstrToAllListeningQueues(std::shared_ptr<Instruction> instr_ptr);

  void addInstrToUpdateQueue(std::shared_ptr<Instruction> instr_ptr);

protected:
  //Calls checkAndNotifyUpdates until the match's ExitInstruction is popped and asked to
  //makeActionAndNotify. This throws a running exception that is catched and
  //execution ends.
  void run() override;

private:
  ClientData askClientData(Socket &socket, uint16_t client_id);

  std::list<ClientData::Role> getAvailableRoles();

  void runCatchingExceptions() override;
};


#endif //QUANTUM_CHESS_PROJ_MATCH_H
