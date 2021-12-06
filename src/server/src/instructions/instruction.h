#ifndef QUANTUM_CHESS_PROJ_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_INSTRUCTION_H

#include <string>
#include <list>
#include "../quantum_chess/board.h"
#include "../../../common/src/packet.h"
#include "../server_protocol.h"
#include "../../../common/src/blocking_queue.h"
#include "../../../common/src/client_data.h"
#include "../match.h"
#include <vector>

class ServerProtocol;

class ClientHandler;

class Match;

class Instruction {
public:
  Instruction() = default;

  //Given the list of listening queues and the client's vector, it makes the appropiate action
  //and notifies all queues of the changes.
  virtual void makeActionAndNotify(Match &match) = 0;

  //The derived Instruction class asks the protocol to fill the given packet with the information
  //accordingly.
  virtual void
  fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                   const ClientData &client_receiver_data) = 0;

  virtual ~Instruction() = default;
};

#endif //QUANTUM_CHESS_PROJ_INSTRUCTION_H
