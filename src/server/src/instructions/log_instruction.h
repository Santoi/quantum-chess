#ifndef QUANTUM_CHESS_PROJ_LOG_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_LOG_INSTRUCTION_H

#include "instruction.h"
#include "../quantum_chess/board.h"

class LogInstruction : public Instruction {
private:
  std::list<std::string> log;

public:
  LogInstruction() = delete;

  //Creates a ChatInstruction, saving the client_id and message passed to the function parameters.
  LogInstruction(std::list<std::string> &&log_);

  //Creates a new ChatInstruction and sends it to all listening queues.
  void makeActionAndNotify(Match &match) override;

  //Gets the instructor's nickname from the ClientDataRepository using the object's instructor_id
  //attribute, and calls the protocol method fillPacketWithChatInfo to fill the given packet.
  void
  fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                   const ClientData &client_receiver_data) override;

  ~LogInstruction() = default;
};


#endif //QUANTUM_CHESS_PROJ_LOG_INSTRUCTION_H
