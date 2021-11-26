#ifndef QUANTUM_CHESS_PROJ_SAME_CHESSMAN_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_SAME_CHESSMAN_INSTRUCTION_H

#include "instruction.h"

class SameChessmanInstruction : public Instruction {
  const ClientData &instructor_data;
  const std::list<Position> positions;

public:
  SameChessmanInstruction(const ClientData &instructor_data,
                          std::list<Position> &&pos);

  void makeActionAndNotifyAllListeningQueues(
          std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
          Match &match,
          BlockingQueue<Instruction> &match_queues_update) override;

  void
  fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                   const ClientData &client_receiver_data) override;
};


#endif //QUANTUM_CHESS_PROJ_SAME_CHESSMAN_INSTRUCTION_H
