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


void SplitInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {
  // TODO validar color, permisos, etc
  try {
    if (instructor_data.role == ClientData::ROLE_SPECTATOR)
      throw ChessException("you cannot move been spectator");
    match.getBoard().split(from, to1, to2,
                           instructor_data.role == ClientData::ROLE_WHITE);
  }
  catch (const ChessException &e) {
    ChessExceptionInstruction instruction(instructor_data, e.what());
    match_updates_queue.push(
            std::make_shared<ChessExceptionInstruction>(instruction));
    return;
  }
  LoadBoardInstruction instruction;
  match_updates_queue.push(
          std::make_shared<LoadBoardInstruction>(instruction));

  std::list<std::string> log;
  match.getBoard().popLog(log);
  // Send Log
  auto log_ptr = std::make_shared<LogInstruction>(
          std::move(log));
  for (auto &listening_queue: listening_queues)
    listening_queue.second.push(log_ptr);

  auto this_instr_ptr = std::make_shared<SoundInstruction>(
          SPLIT_SOUND);
  for (auto it = listening_queues.begin(); it != listening_queues.end(); ++it)
    it->second.push(this_instr_ptr);
}

void
SplitInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                   Packet &packet,
                                                   const ClientData &client_receiver_data) {
}