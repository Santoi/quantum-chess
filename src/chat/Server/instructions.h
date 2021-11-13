#ifndef QUANTUM_CHESS_PROJ_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_INSTRUCTION_H

#include <string>
#include <list>
#include "common_packet.h"
#include "nick_names_repository.h"
#include "server_protocol.h"
#include <vector>

class ServerProtocol;

class BlockingQueue;

class ClientHandler;

class Instruction {
private:


public:
    Instruction() = default;
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                       std::vector<ClientHandler>& clients);
    virtual void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                  const NickNamesRepository& nick_names,
                                                  const int& client_receiver_id);
    ~Instruction() = default;
};

class ChatInstruction: public Instruction {
private:
    const int instructor_id;
    std::string message;

public:
    ChatInstruction() = delete;
    ChatInstruction(const int& client_id, std::string&& message);
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                       std::vector<ClientHandler>& clients);
    virtual void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                  const NickNamesRepository& nick_names,
                                                  const int& client_receiver_id);
    ~ChatInstruction() = default;
};

class ExitInstruction: public Instruction {
private:
    const int instructor_id;

public:
    ExitInstruction() = delete;
    ExitInstruction(const int& client_id);
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                       std::vector<ClientHandler>& clients);
    virtual void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                  const NickNamesRepository& nick_names,
                                                  const int& client_receiver_id);
    ~ExitInstruction() = default;
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
