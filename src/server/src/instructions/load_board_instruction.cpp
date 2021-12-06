#include <vector>
#include "load_board_instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "../../../client/position.h" // TODO: can use server's position?


// TODO ver si hacer una clase chessman_data o incluir la de common.
LoadBoardInstruction::LoadBoardInstruction()
        : positions(), characters(), colors(), probabilities(), white(true) {}


void LoadBoardInstruction::makeActionAndNotify(Match &match) {
  match.getBoard().loadVectors(characters, colors, positions, probabilities);
  white = match.getBoard().isNextWhite();
  std::shared_ptr<Instruction> this_instruct_ptr = std::make_shared<LoadBoardInstruction>(
          std::move(*this));
  match.addInstrToAllListeningQueues(this_instruct_ptr);
}

void
LoadBoardInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                       Packet &packet,
                                                       const ClientData &client_receiver_data) {
  protocol.fillPacketWithLoadBoardInfo(packet, characters, colors, positions,
                                       probabilities, white);
}