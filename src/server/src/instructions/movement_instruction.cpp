#include "movement_instruction.h"
#include "load_board_instruction.h"
#include "../quantum_chess/chess_exception.h"
#include "chess_exception_instruction.h"

MovementInstruction::MovementInstruction(const ClientData &instructor_data,
                                         const Position &initial_,
                                         const Position &final_) :
        instructor_data(instructor_data),
        initial(initial_), final(final_) {}


void MovementInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {
  // TODO validar color, permisos, etc
  try {
    match.getBoard().move(initial, final);
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
}

void
MovementInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                      Packet &packet,
                                                      const ClientData &client_receiver_data) {
}