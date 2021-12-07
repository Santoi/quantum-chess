#ifndef QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H

#include "../../../client/position.h" // TODO: can use server's position?
#include "instruction.h"
#include "../../../common/src/blocking_queue.h"

class LoadBoardInstruction : public Instruction {
  std::vector<Position> positions;
  std::vector<char> characters;
  std::vector<bool> colors;
  std::vector<double> probabilities;
  bool white;

public:
  LoadBoardInstruction();

  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData &client_receiver_data) override;


};


#endif //QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
