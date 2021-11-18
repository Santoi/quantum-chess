#include <vector>
#include "load_board_instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "../../../client/src/position.h"

LoadBoardInstruction::LoadBoardInstruction(): characters(), positions(), colors(){}


void LoadBoardInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<int, BlockingQueue<Instruction>> &listening_queues,
        std::map<int, ClientHandler>& clients, Board & board,
        BlockingQueue<Instruction> & match_updates_queue) {
    board.loadVectors(characters, colors, positions);
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<LoadBoardInstruction>(std::move(*this));
    for (auto it = listening_queues.begin(); it != listening_queues.end(); ++it)
        it->second.push(this_instruc_ptr);
}

void LoadBoardInstruction::fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                       const NickNamesRepository& nick_names,
                                                       const int& client_receiver_id) {
    protocol.fillPacketWithLoadBoardInfo(packet, characters, colors, positions);
}