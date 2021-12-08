#ifndef QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H

#include "../quantum_chess/position.h"
#include "../quantum_chess/square_data.h"
#include "instruction.h"
#include "../../../common/src/blocking_queue.h"

class LoadBoardInstruction : public Instruction {
  std::vector<SquareData> data;
  bool white;

public:
  LoadBoardInstruction();

  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData &client_receiver_data) override;


};


#endif //QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
