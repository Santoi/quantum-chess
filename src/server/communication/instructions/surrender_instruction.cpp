#include "surrender_instruction.h"
#include "log_instruction.h"
#include "../../../common/chess_exception.h"
#include "chess_exception_instruction.h"

SurrenderInstruction::SurrenderInstruction(const ClientData &instructor_data_)
                    :instructor_data(instructor_data_) {
}

void SurrenderInstruction::makeActionAndNotify(Match &match) {
  try {
    match.getBoard().surrender(instructor_data.role);
    std::shared_ptr<Instruction> this_instruct_ptr = std::make_shared<SurrenderInstruction>(
            instructor_data);
    match.addInstrToAllListeningQueues(this_instruct_ptr);
  } catch (const ChessException &e) {
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


void SurrenderInstruction::fillPacketWithInstructionToSend(ServerProtocol &protocol,
                                                           Packet &packet,
                                                           const ClientData &client_receiver_data) {}