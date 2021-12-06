#ifndef QUANTUM_CHESS_PROJ_MOVEMENT_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_MOVEMENT_INSTRUCTION_H

#include "instruction.h"
#include "../quantum_chess/position.h"

class MovementInstruction : public Instruction {
  const ClientData &instructor_data;
  const Position initial;
  const Position final;

public:
  MovementInstruction(const ClientData &instructor_data,
                      const Position &initial_,
                      const Position &final_);

  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                   const ClientData &client_receiver_data) override;
};


#endif //QUANTUM_CHESS_PROJ_MOVEMENT_INSTRUCTION_H
