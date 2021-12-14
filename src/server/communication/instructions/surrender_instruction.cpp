#include "surrender_instruction.h"
#include "log_instruction.h"
#include "../../../common/chess_exception.h"
#include "chess_exception_instruction.h"
#include <string>
#include <list>

SurrenderInstruction::SurrenderInstruction(const ClientData &instructor_data_)
    : instructor_data(instructor_data_) {
}

void SurrenderInstruction::makeActionAndNotify(Match &match) {
  try {
    if (instructor_data.role == ClientData::ROLE_SPECTATOR)
      throw ChessException("Spectator cannot surrender");
    match.getBoard().surrender(instructor_data.role ==
                               ClientData::ROLE_WHITE);
  } catch(const ChessException &e) {
    std::shared_ptr<Instruction> error_instr =
        std::make_shared<ChessExceptionInstruction>(instructor_data,
                                                    e.what());
    match.addInstrToClientListeningQueue(instructor_data.id, error_instr);
    return;
  }
  std::list<std::string> log;
  match.getBoard().popLog(log);
  std::shared_ptr<Instruction> log_ptr = std::make_shared<LogInstruction>(
      std::move(log));
  match.addInstrToAllListeningQueues(log_ptr);
}


void
SurrenderInstruction::fillPacketWithInstructionToSend(ServerProtocol &protocol,
                                                      Packet &packet,
                                                      const ClientData
                                                      &client_receiver_data) {}
