#ifndef QUANTUM_CHESS_PROJ_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_INSTRUCTION_H

#include <string>
#include <list>
#include "../../../common/src/packet.h"
#include "../nick_names_repository.h"
#include "../server_protocol.h"
#include <vector>

#define MATCH_ID -1

class ServerProtocol;

class BlockingQueue;

class ClientHandler;

class Instruction {
private:


public:
    Instruction() = default;

    //Given the list of listening queues and the client's vector, it makes the appropiate action
    //and notifies all queues of the changes.
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                       std::vector<ClientHandler>& clients);

    //The derived Instruction class asks the protocol to fill the given packet with the information
    //accordingly.
    virtual void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                  const NickNamesRepository& nick_names,
                                                  const int& client_receiver_id) = 0;

    ~Instruction() = default;
};

/*
class MovementInstruction: public Instruction {
private:
    const int instructor_id;
public:
    MovementInstruction(const int& client_id);
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues);
    virtual void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet
                                                   const NickNamesRepository& nick_names);
};*/

#endif //QUANTUM_CHESS_PROJ_INSTRUCTION_H
