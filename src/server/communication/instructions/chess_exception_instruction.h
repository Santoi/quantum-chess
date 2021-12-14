#ifndef QUANTUM_CHESS_PROJ_CHESS_EXCEPTION_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_CHESS_EXCEPTION_INSTRUCTION_H

#include "../../../common/client_data.h"
#include "instruction.h"
#include <map>
#include <string>

class Instruction;

class ChessExceptionInstruction : public Instruction {
private:
  const ClientData &instructor_data;
  std::string message;

public:
  ChessExceptionInstruction() = delete;

  ChessExceptionInstruction(const ClientData &instructor_data_,
                            std::string &&message);

  // Does nothing
  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData
                                  &client_receiver_data) override;

  ~ChessExceptionInstruction() override = default;
};


#endif //QUANTUM_CHESS_PROJ_CHESS_EXCEPTION_INSTRUCTION_H
