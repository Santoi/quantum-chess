#include <vector>
#include "load_board_instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "../../../client/position.h" // TODO: can use server's position?


// TODO ver si hacer una clase chessman_data o incluir la de common.
LoadBoardInstruction::LoadBoardInstruction(): characters(), positions(), colors(), probabilities(){}


void LoadBoardInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        std::map<uint16_t, ClientHandler>& clients, Board & board,
        BlockingQueue<Instruction> & match_updates_queue) {
  board.loadVectors(characters, colors, positions, probabilities);
  std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<LoadBoardInstruction>(std::move(*this));
  for (auto it = listening_queues.begin(); it != listening_queues.end(); ++it)
    it->second.push(this_instruc_ptr);
}

void
LoadBoardInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                       Packet &packet,
                                                       const ClientData &client_receiver_data) {
  protocol.fillPacketWithLoadBoardInfo(packet, characters, colors, positions,
                                       probabilities);
}