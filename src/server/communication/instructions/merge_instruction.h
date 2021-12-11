#ifndef QUANTUM_CHESS_PROJ_MERGE_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_MERGE_INSTRUCTION_H

#include "instruction.h"
#include "../../quantum_chess/position.h"

class MergeInstruction : public Instruction {
  const ClientData &instructor_data;
  const Position from1;
  const Position from2;
  const Position to;

public:
  MergeInstruction(const ClientData &instructor_data,
                   const Position &from1_, const Position &from2_,
                   const Position &to_);

  // Performs merge in board, send event log and sound.
  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData &client_receiver_data) override;
};


#endif //QUANTUM_CHESS_PROJ_MERGE_INSTRUCTION_H
