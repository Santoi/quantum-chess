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

  // Performs the instruction action and notifies
  virtual void makeActionAndNotify(Match &match) = 0;

  // Loads a packet with instruction to be sent to client.
  virtual void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData &client_receiver_data) = 0;

  virtual ~Instruction() = default;
};

#endif //QUANTUM_CHESS_PROJ_INSTRUCTION_H
