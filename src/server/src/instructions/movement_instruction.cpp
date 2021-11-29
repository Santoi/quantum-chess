#include "movement_instruction.h"
#include "load_board_instruction.h"
#include "../../../common/src/chess_exception.h"
#include "chess_exception_instruction.h"
#include "sound_instruction.h"

MovementInstruction::MovementInstruction(const ClientData &instructor_data,
                                         const Position &initial_,
                                         const Position &final_) :
        instructor_data(instructor_data),
        initial(initial_), final(final_) {}


void MovementInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {
  // TODO validar color, permisos, etc
  bool capture = false;
  try {
    if (instructor_data.role == ClientData::ROLE_SPECTATOR)
      throw ChessException("you cannot move been spectator");
    capture = match.getBoard().move(initial, final,
                                    instructor_data.role ==
                                    ClientData::ROLE_WHITE);
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
  if (capture) {
    auto this_instr_ptr = std::make_shared<SoundInstruction>(
            CAPTURE_SOUND);
    for (auto it = listening_queues.begin(); it != listening_queues.end(); ++it)
      it->second.push(this_instr_ptr);
  }
}

void
MovementInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                      Packet &packet,
                                                      const ClientData &client_receiver_data) {
}