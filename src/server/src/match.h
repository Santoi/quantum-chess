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

// Thread that represents a chess match. Has stored the board and clients.
class Match : public Thread {
private:
  Board board;
  ClientsMap clients_map;
  BlockingQueue<Instruction> match_updates_queue;
  std::ifstream &file;

  // Pops and instruction from the update queue and perform its action.
  void checkAndNotifyUpdates();

public:
  // Constructor. Receives an ifstream reference to file with board.
  Match(std::ifstream &file_);

  Match(Match &&other);

  ~Match() override = default;

  // Adds client to match and start its threads.
  void addClientToMatch(Socket &&client_socket, uint16_t client_id);

  // Returns true if the match has any active client.
  bool hasActiveClients();

  // Stop the thread closing the updates queue.
  void stop();

  // Returns a vector with data of clients in match.
  void loadWithClientData(std::vector<ClientData> &vector) const;

  // Deletes a client with id.
  void deleteClientWithId(uint16_t client_id);

  // Return a reference to match board.
  Board &getBoard();

  // Adds an instruction to the clients listening queue.
  void addInstrToClientListeningQueue(uint16_t client_id,
                                      std::shared_ptr<Instruction> &instr_ptr);

  // Adds an instruction to all clients listening queues.
  void addInstrToAllListeningQueues(std::shared_ptr<Instruction> instr_ptr);

  // Adds an instruction to the update queue.
  void addInstrToUpdateQueue(std::shared_ptr<Instruction> instr_ptr);

protected:
  // Checks updates queue and perform actions until instruction of exit is
  // received.
  void run() override;

private:
  // Ask client for data and returns a ClientData instruction with it.
  ClientData askClientData(Socket &socket, uint16_t client_id);

  // TODO pasar referencia?
  // Returns a list of roles availables.
  std::list<ClientData::Role> getAvailableRoles();

  void runCatchingExceptions() override;
};


#endif //QUANTUM_CHESS_PROJ_MATCH_H
