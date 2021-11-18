#ifndef QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H

#include "../../../client/src/position.h"
#include "instruction.h"
#include "../../../common/src/blocking_queue.h"

class LoadBoardInstruction: public Instruction {
    std::vector<Position> positions;
    std::vector<char> characters;
    std::vector<bool> colors;

public:
    LoadBoardInstruction();

    void makeActionAndNotifyAllListeningQueues(
            std::map<int, BlockingQueue<Instruction>> &listening_queues,
            std::map<int, ClientHandler>& clients,
            Board & board, BlockingQueue<Instruction> & match_updates_queue) override;

    void
    fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                     const NickNamesRepository &nick_names,
                                     const int &client_receiver_id) override;


};


#endif //QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
