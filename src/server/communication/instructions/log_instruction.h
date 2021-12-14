#ifndef QUANTUM_CHESS_PROJ_LOG_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_LOG_INSTRUCTION_H

#include "instruction.h"
#include "../../quantum_chess/board.h"
#include <list>
#include <string>

class LogInstruction : public Instruction {
private:
  std::list<std::string> log;

public:
  LogInstruction() = delete;

  explicit LogInstruction(std::list<std::string> &&log_);

  // Send log message to all clients.
  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData
                                  &client_receiver_data) override;

  ~LogInstruction() override = default;
};


#endif //QUANTUM_CHESS_PROJ_LOG_INSTRUCTION_H
