#ifndef QUANTUM_CHESS_PROJ_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_INSTRUCTION_H

#include <string>
#include <list>
#include "../quantum_chess/board.h"
#include "../../../common/src/packet.h"
#include "../nick_names_repository.h"
#include "../server_protocol.h"
#include "../../../common/src/blocking_queue.h"
#include <vector>

#define MATCH_ID -1

class ServerProtocol;

class ClientHandler;

class Instruction {
public:
    Instruction() = default;

    //Given the list of listening queues and the client's vector, it makes the appropiate action
    //and notifies all queues of the changes.
    virtual void makeActionAndNotifyAllListeningQueues(
            std::map<int, BlockingQueue<Instruction>> &listening_queues,
            std::map<int, ClientHandler>& clients,
            Board & board, BlockingQueue<Instruction> & match_updates_queue) = 0;

    //The derived Instruction class asks the protocol to fill the given packet with the information
    //accordingly.
    virtual void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                  const NickNamesRepository& nick_names,
                                                  const int& client_receiver_id) = 0;

    ~Instruction() = default;
};

#endif //QUANTUM_CHESS_PROJ_INSTRUCTION_H
