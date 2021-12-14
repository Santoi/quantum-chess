#ifndef QUANTUM_CHESS_PROJ_EXIT_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_EXIT_INSTRUCTION_H

#include <string>
#include <list>
#include "instruction.h"
#include "../../../common/packet.h"
#include "../server_protocol.h"
#include <vector>

class ExitInstruction : public Instruction {
private:
  // It is copied because client is destroyed
  ClientData instructor_data;

public:
  ExitInstruction() = delete;

  explicit ExitInstruction(const ClientData &instructor_data_);

  void makeActionAndNotify(Match &match) override;

  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol,
                                  Packet &packet,
                                  const ClientData
                                  &client_receiver_data) override;

  ~ExitInstruction() override = default;
};


#endif //QUANTUM_CHESS_PROJ_EXIT_INSTRUCTION_H
