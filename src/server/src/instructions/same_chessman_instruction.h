#ifndef QUANTUM_CHESS_PROJ_SAME_CHESSMAN_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_SAME_CHESSMAN_INSTRUCTION_H

#include "instruction.h"

class SameChessmanInstruction : public Instruction {
  const ClientData &instructor_data;
  const std::list<Position> positions;

public:
  SameChessmanInstruction(const ClientData &instructor_data,
                          std::list<Position> &&pos);

  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData &client_receiver_data) override;
};


#endif //QUANTUM_CHESS_PROJ_SAME_CHESSMAN_INSTRUCTION_H
