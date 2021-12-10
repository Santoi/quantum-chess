#ifndef QUANTUM_CHESS_PROJ_CHAT_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_CHAT_INSTRUCTION_H

#include "instruction.h"
#include "../quantum_chess/board.h"

class ChatInstruction : public Instruction {
private:
  const ClientData instructor_data;
  std::string message;

  // Returns a string with timestamp.
  std::string getTimeStamp();

public:
  ChatInstruction() = delete;

  ChatInstruction(const ClientData &instructor_data_, std::string &&message);

  // Copies itself into clients listening queues.
  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData &client_receiver_data) override;

  ~ChatInstruction() override = default;
};


#endif //QUANTUM_CHESS_PROJ_CHAT_INSTRUCTION_H
