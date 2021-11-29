#include "entangled_chessman_instruction.h"
#include "chess_exception_instruction.h"
#include "../../../common/src/chess_exception.h"

EntangledChessmanInstruction::EntangledChessmanInstruction(
        const ClientData &inst_data,
        std::list<Position> &&pos) :
        instructor_data(inst_data),
        positions(std::move(pos)) {}


void EntangledChessmanInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {
  std::list<Position> positions_;
  try {
    positions_ = match.getBoard().getEntangledOf(*positions.begin());
  }
  catch (const ChessException &e) {
    ChessExceptionInstruction instruction(instructor_data, e.what());
    match_updates_queue.push(
            std::make_shared<ChessExceptionInstruction>(instruction));
    return;
  }
  std::shared_ptr<Instruction> this_instruc_ptr =
          std::make_shared<EntangledChessmanInstruction>(instructor_data,
                                                         std::move(positions_));
  listening_queues.at(instructor_data.id).push(this_instruc_ptr);
}

void
EntangledChessmanInstruction::fillPacketWithInstructionsToSend(
        ServerProtocol &protocol,
        Packet &packet,
        const ClientData &client_receiver_data) {
  protocol.fillPacketWithEntangledChessmanInstruction(packet, positions);
}