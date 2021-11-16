#ifndef QUANTUM_CHESS_PROJ_MOVEMENT_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_MOVEMENT_INSTRUCTION_H

#include "instruction.h"
#include "../quantum_chess/position.h"

class MovementInstruction: public Instruction {
    const int instructor_id;
    const Position initial;
    const Position final;

public:
    MovementInstruction(const int &client_id, const Position &initial_,
                        const Position &final_);

    void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue<Instruction>> &listening_queues,
                                               std::vector<ClientHandler> &clients, Board &board) override;

    void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                  const NickNamesRepository& nick_names,
                                                  const int& client_receiver_id) override;
};


#endif //QUANTUM_CHESS_PROJ_MOVEMENT_INSTRUCTION_H
