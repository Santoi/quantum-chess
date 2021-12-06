#include "split_instruction.h"
#include "load_board_instruction.h"
#include "../../../common/src/chess_exception.h"
#include "chess_exception_instruction.h"
#include "sound_instruction.h"
#include "log_instruction.h"

SplitInstruction::SplitInstruction(const ClientData &instructor_data,
                                   const Position &from_,
                                   const Position &to1_,
                                   const Position &to2_) :
        instructor_data(instructor_data),
        from(from_), to1(to1_), to2(to2_) {}


void SplitInstruction::makeActionAndNotify(Match &match) {
  // TODO validar color, permisos, etc
  try {
    if (instructor_data.role == ClientData::ROLE_SPECTATOR)
      throw ChessException("you cannot move been spectator");
    match.getBoard().split(from, to1, to2,
                           instructor_data.role == ClientData::ROLE_WHITE);
  }
  catch (const ChessException &e) {
    std::shared_ptr<Instruction> error_instr =
            std::make_shared<ChessExceptionInstruction>(instructor_data,
                                                        e.what());
    match.addInstrToClientListeningQueue(instructor_data.id, error_instr);
    return;
  }
  std::shared_ptr<Instruction> this_instruct_ptr =
          std::make_shared<LoadBoardInstruction>();
  match.addInstrToUpdateQueue(this_instruct_ptr);

  std::list<std::string> log;
  match.getBoard().popLog(log);
  // Send Log
  auto log_ptr = std::make_shared<LogInstruction>(
          std::move(log));
  match.addInstrToAllListeningQueues(log_ptr);

  std::shared_ptr<Instruction> sound_str =
          std::make_shared<SoundInstruction>(SPLIT_SOUND);
  match.addInstrToAllListeningQueues(sound_str);
}

void
SplitInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                   Packet &packet,
                                                   const ClientData &client_receiver_data) {
}