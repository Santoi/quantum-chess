#ifndef QUANTUM_CHESS_PROJ_SPLIT_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_SPLIT_INSTRUCTION_H

#include "instruction.h"
#include "../../quantum_chess/position.h"

class SplitInstruction : public Instruction {
  const ClientData &instructor_data;
  const Position from;
  const Position to1;
  const Position to2;

public:
  SplitInstruction(const ClientData &instructor_data,
                   const Position &from_, const Position &to1_,
                   const Position &to2_);

  // Performs a split on the board.
  void makeActionAndNotify(Match &match) override;

  // Does nothing.
  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData
                                  &client_receiver_data) override;
};


#endif //QUANTUM_CHESS_PROJ_SPLIT_INSTRUCTION_H
