#ifndef QUANTUM_CHESS_PROJ_CHAT_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_CHAT_INSTRUCTION_H

#include "instruction.h"
#include "../quantum_chess/board.h"

class ChatInstruction : public Instruction {
private:
  const ClientData &instructor_data;
  std::string message;

public:
  ChatInstruction() = delete;

  //Creates a ChatInstruction, saving the client_id and message passed to the function parameters.
  ChatInstruction(const ClientData &instructor_data_, std::string &&message);

  //Creates a new ChatInstruction and sends it to all listening queues.
  void makeActionAndNotifyAllListeningQueues(
          std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
          Match &match,
          BlockingQueue<Instruction> &match_updates_queue) override;

  //Gets the instructor's nickname from the ClientDataRepository using the object's instructor_id
  //attribute, and calls the protocol method fillPacketWithChatInfo to fill the given packet.
  void
  fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                   const ClientData &client_receiver_data) override;

  ~ChatInstruction() = default;
};


#endif //QUANTUM_CHESS_PROJ_CHAT_INSTRUCTION_H
