#ifndef QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H

#include "../../quantum_chess/position.h"
#include "../../quantum_chess/client_data.h"
#include "instruction.h"
#include "../../../common/blocking_queue.h"

class LoadBoardInstruction : public Instruction {
  std::vector<SquareData> data;
  bool white;

public:
  LoadBoardInstruction();

  // Loads data from vector and notifies all clients.
  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData &client_receiver_data) override;

  ~LoadBoardInstruction() override = default;
};


#endif //QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
