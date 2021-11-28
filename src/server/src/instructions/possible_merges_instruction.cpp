#include "possible_merges_instruction.h"
#include "chess_exception_instruction.h"
#include "../quantum_chess/chess_exception.h"

PossibleMergesInstruction::PossibleMergesInstruction(
        const ClientData &inst_data,
        std::list<Position> &&pos) :
        instructor_data(inst_data),
        positions(std::move(pos)) {}


void PossibleMergesInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {
  std::list<Position> positions_;
  try {
    if (positions.size() == 1)
      positions_ = match.getBoard().getPossibleMergesOf(*positions.begin());
    else
      positions_ = match.getBoard().getPossibleMergesOf(*positions.begin(),
                                                        *(++positions.begin()));
  }
  catch (const ChessException &e) {
    ChessExceptionInstruction instruction(instructor_data, e.what());
    match_updates_queue.push(
            std::make_shared<ChessExceptionInstruction>(instruction));
    return;
  }
  std::shared_ptr<Instruction> this_instruc_ptr =
          std::make_shared<PossibleMergesInstruction>(instructor_data,
                                                      std::move(positions_));
  listening_queues.at(instructor_data.id).push(this_instruc_ptr);
}

void
PossibleMergesInstruction::fillPacketWithInstructionsToSend(
        ServerProtocol &protocol,
        Packet &packet,
        const ClientData &client_receiver_data) {
  protocol.fillPacketWithPossibleMerges(packet, positions);
}