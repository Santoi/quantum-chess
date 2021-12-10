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

  // Performs move in board, send event log and sound if a chessman is captured.
  void makeActionAndNotify(Match &match) override;

  // Does nothing
  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData
                                  &client_receiver_data) override;
};


#endif //QUANTUM_CHESS_PROJ_MOVEMENT_INSTRUCTION_H
