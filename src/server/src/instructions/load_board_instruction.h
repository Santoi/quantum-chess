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

public:
  LoadBoardInstruction();

  void makeActionAndNotifyAllListeningQueues(
          std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
          Match &match,
          BlockingQueue<Instruction> &match_updates_queue) override;

  void
  fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                   const ClientData &client_receiver_data) override;


};


#endif //QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
