#include "merge_instruction.h"
#include "load_board_instruction.h"
#include "../../../common/src/chess_exception.h"
#include "chess_exception_instruction.h"
#include "sound_instruction.h"
#include "log_instruction.h"

MergeInstruction::MergeInstruction(const ClientData &instructor_data,
                                   const Position &from1_,
                                   const Position &from2_,
                                   const Position &to_) :
        instructor_data(instructor_data),
        from1(from1_), from2(from2_), to(to_) {}


void MergeInstruction::makeActionAndNotify(Match &match) {
  try {
    if (instructor_data.role == ClientData::ROLE_SPECTATOR)
      throw ChessException("you cannot move been spectator");
    match.getBoard().merge(from1, from2, to,
                           instructor_data.role == ClientData::ROLE_WHITE);
  }
  catch (const ChessException &e) {
    std::shared_ptr<Instruction> error_instr =
            std::make_shared<ChessExceptionInstruction>(instructor_data,
                                                        e.what());
    match.addInstrToClientListeningQueue(instructor_data.id, error_instr);
    return;
  }
  std::shared_ptr<Instruction> load_board_instr =
          std::make_shared<LoadBoardInstruction>();
  match.addInstrToUpdateQueue(load_board_instr);

  std::list<std::string> log;
  match.getBoard().popLog(log);
  std::shared_ptr<Instruction> log_ptr = std::make_shared<LogInstruction>(
          std::move(log));
  match.addInstrToAllListeningQueues(log_ptr);


  std::shared_ptr<Instruction> sound_instr = std::make_shared<SoundInstruction>(
          MERGE_SOUND);
  match.addInstrToAllListeningQueues(sound_instr);

}

void
MergeInstruction::fillPacketWithInstructionToSend(ServerProtocol &protocol,
                                                  Packet &packet,
                                                  const ClientData &client_receiver_data) {}