#include "possible_merges_instruction.h"
#include "chess_exception_instruction.h"
#include "../../../common/chess_exception.h"
#include <list>

PossibleMergesInstruction::PossibleMergesInstruction(
    const ClientData &inst_data,
    std::list<Position> &&pos) :
    instructor_data(inst_data),
    positions(std::move(pos)) {}


void PossibleMergesInstruction::makeActionAndNotify(Match &match) {
  std::list<Position> positions_;
  try {
    if (positions.size() == 1)
      match.getBoard().getPossibleMergesOf(*positions.begin(),
                                           positions_);
    else
      match.getBoard().getPossibleMergesOf(*positions.begin(),
                                           *(++positions.begin()),
                                           positions_);
  }
  catch(const ChessException &e) {
    std::shared_ptr<Instruction> error_instr =
        std::make_shared<ChessExceptionInstruction>(instructor_data,
                                                    e.what());
    match.addInstrToClientListeningQueue(instructor_data.id, error_instr);
    return;
  }
  std::shared_ptr<Instruction> this_instruct_ptr =
      std::make_shared<PossibleMergesInstruction>(instructor_data,
                                                  std::move(positions_));
  match.addInstrToClientListeningQueue(instructor_data.id, this_instruct_ptr);
}

void
PossibleMergesInstruction::fillPacketWithInstructionToSend(
    ServerProtocol &protocol,
    Packet &packet,
    const ClientData &client_receiver_data) {
  protocol.fillPacketWithPossibleMerges(packet, positions);
}
