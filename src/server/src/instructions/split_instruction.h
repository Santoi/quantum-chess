#ifndef QUANTUM_CHESS_PROJ_SPLIT_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_SPLIT_INSTRUCTION_H

#include "instruction.h"
#include "../quantum_chess/position.h"

class SplitInstruction : public Instruction {
  const ClientData &instructor_data;
  const Position from;
  const Position to1;
  const Position to2;

public:
  SplitInstruction(const ClientData &instructor_data,
                   const Position &from_, const Position &to1_,
                   const Position &to2_);

  void makeActionAndNotifyAllListeningQueues(
          std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
          Match &match,
          BlockingQueue<Instruction> &match_queues_update) override;

  void
  fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                   const ClientData &client_receiver_data) override;
};


#endif //QUANTUM_CHESS_PROJ_SPLIT_INSTRUCTION_H
