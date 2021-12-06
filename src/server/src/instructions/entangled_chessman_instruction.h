#ifndef QUANTUM_CHESS_PROJ_ENTANGLED_CHESSMAN_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_ENTANGLED_CHESSMAN_INSTRUCTION_H

#include "instruction.h"

class EntangledChessmanInstruction : public Instruction {
  const ClientData &instructor_data;
  const std::list<Position> positions;

public:
  EntangledChessmanInstruction(const ClientData &instructor_data,
                               std::list<Position> &&pos);

  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                   const ClientData &client_receiver_data) override;
};


#endif //QUANTUM_CHESS_PROJ_ENTANGLED_CHESSMAN_INSTRUCTION_H
