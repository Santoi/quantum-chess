#ifndef QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H


#include "../../../client/src/position.h"
#include "instruction.h"

class LoadBoardInstruction: public Instruction {
    std::vector<Position> positions;
    std::vector<char> characters;

public:
    LoadBoardInstruction();

    void makeActionAndNotifyAllListeningQueues(
            std::list<BlockingQueue<Instruction>> &listening_queues,
            std::vector<ClientHandler> &clients, Board &board) override;

    void
    fillPacketWithInstructionsToSend(ServerProtocol &protocol, Packet &packet,
                                     const NickNamesRepository &nick_names,
                                     const int &client_receiver_id) override;
};


#endif //QUANTUM_CHESS_PROJ_LOAD_BOARD_INSTRUCTION_H
