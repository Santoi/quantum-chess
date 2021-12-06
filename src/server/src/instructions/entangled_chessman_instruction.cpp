#include "entangled_chessman_instruction.h"
#include "chess_exception_instruction.h"
#include "../../../common/src/chess_exception.h"

EntangledChessmanInstruction::EntangledChessmanInstruction(
        const ClientData &inst_data,
        std::list<Position> &&pos) :
        instructor_data(inst_data),
        positions(std::move(pos)) {}


void EntangledChessmanInstruction::makeActionAndNotify(Match &match) {
  std::list<Position> positions_;
  try {
    match.getBoard().getEntangledOf(*positions.begin(),
                                    positions_);
  }
  catch (const ChessException &e) {
    std::shared_ptr<Instruction> error_instr =
            std::make_shared<ChessExceptionInstruction>(instructor_data,
                                                        e.what());
    match.addInstrToClientListeningQueue(instructor_data.id, error_instr);
    return;
  }
  std::shared_ptr<Instruction> this_instruct_ptr =
          std::make_shared<EntangledChessmanInstruction>(instructor_data,
                                                         std::move(positions_));
  match.addInstrToClientListeningQueue(instructor_data.id, this_instruct_ptr);
}

void
EntangledChessmanInstruction::fillPacketWithInstructionsToSend(
        ServerProtocol &protocol,
        Packet &packet,
        const ClientData &client_receiver_data) {
  protocol.fillPacketWithEntangledChessmanInstruction(packet, positions);
}