#ifndef QUANTUM_CHESS_PROJ_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_INSTRUCTION_H

#include <string>
#include <list>
#include "common_packet.h"

class BlockingQueue;

class Instruction {

public:
    Instruction() = default;
    void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues);
    void fillPacketWithInstructionsToSend(Packet& packet);
    ~Instruction() = default;
};

class ChatInstruction: public Instruction {
private:
    std::string message;

public:
    ChatInstruction() = delete;
    ChatInstruction(std::string&& message);
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues);
    virtual void fillPacketWithInstructionsToSend(Packet& packet);
    ~ChatInstruction() = default;
};

class MovementInstruction: public Instruction {
public:
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues);
    virtual void fillPacketWithInstructionsToSend(Packet& packet);
};
#endif //QUANTUM_CHESS_PROJ_INSTRUCTION_H
