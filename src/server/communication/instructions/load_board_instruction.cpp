#include <vector>
#include "load_board_instruction.h"
#include "../../quantum_chess/position.h"

LoadBoardInstruction::LoadBoardInstruction()
    : data(), white(true) {}


void LoadBoardInstruction::makeActionAndNotify(Match &match) {
  match.getBoard().loadVectorOfSquareData(data);
  white = match.getBoard().isNextWhite();
  std::shared_ptr<Instruction> this_instruct_ptr =
      std::make_shared<LoadBoardInstruction>(std::move(*this));
  match.addInstrToAllListeningQueues(this_instruct_ptr);
}

void LoadBoardInstruction::
fillPacketWithInstructionToSend(ServerProtocol &protocol,
                                Packet &packet,
                                const ClientData &client_receiver_data) {
  protocol.fillPacketWithLoadBoardMessage(packet, data, white);
}
