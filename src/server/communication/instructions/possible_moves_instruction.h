#ifndef QUANTUM_CHESS_PROJ_POSSIBLE_MOVES_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_POSSIBLE_MOVES_INSTRUCTION_H

#include "instruction.h"
#include <list>

class PossibleMovesInstruction : public Instruction {
  const ClientData &instructor_data;
  const std::list<Position> positions;

public:
  PossibleMovesInstruction(const ClientData &instructor_data,
                           std::list<Position> &&pos);

  // Gets information about possible moves and sends it to client.
  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol,
                                  Packet &packet,
                                  const ClientData
                                  &client_receiver_data) override;
};


#endif //QUANTUM_CHESS_PROJ_POSSIBLE_MOVES_INSTRUCTION_H
