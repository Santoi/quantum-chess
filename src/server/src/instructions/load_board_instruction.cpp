#include <vector>
#include "load_board_instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "../../../client/src/position.h"

LoadBoardInstruction::LoadBoardInstruction(): characters(), positions(), colors(){}


void LoadBoardInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        std::map<uint16_t, ClientHandler>& clients, Board & board,
        BlockingQueue<Instruction> & match_updates_queue) {
    board.loadVectors(characters, colors, positions);
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<LoadBoardInstruction>(std::move(*this));
    for (auto it = listening_queues.begin(); it != listening_queues.end(); ++it)
        it->second.push(this_instruc_ptr);
}

void
LoadBoardInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                       Packet &packet,
                                                       const ClientData &client_receiver_data) {
    protocol.fillPacketWithLoadBoardInfo(packet, characters, colors, positions);
}