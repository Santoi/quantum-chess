#include "possible_moves_instruction.h"
#include "chess_exception_instruction.h"
#include "../quantum_chess/chess_exception.h"

PossibleMovesInstruction::PossibleMovesInstruction(const ClientData &inst_data,
                                                   std::list<Position> &&pos) :
        instructor_data(inst_data),
        positions(std::move(pos)) {}


void PossibleMovesInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {
  std::list<Position> positions_;
  try {
    positions_ = match.getBoard().getPossibleMovesOf(*positions.begin());
  }
  catch (const ChessException &e) {
    ChessExceptionInstruction instruction(instructor_data, e.what());
    match_updates_queue.push(
            std::make_shared<ChessExceptionInstruction>(instruction));
    return;
  }
  std::shared_ptr<Instruction> this_instruc_ptr =
          std::make_shared<PossibleMovesInstruction>(instructor_data,
                                                     std::move(positions_));
  listening_queues.at(instructor_data.id).push(this_instruc_ptr);
}

void
PossibleMovesInstruction::fillPacketWithInstructionsToSend(
        ServerProtocol &protocol,
        Packet &packet,
        const ClientData &client_receiver_data) {
  protocol.fillPacketWithPossibleMoves(packet, positions);
}