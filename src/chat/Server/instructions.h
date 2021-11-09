#ifndef QUANTUM_CHESS_PROJ_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_INSTRUCTION_H

#include <string>
#include <list>

class BlockingQueue;

class Instruction {

public:
    Instruction() = default;
    void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues);
    ~Instruction() = default;
};

class ChatInstruction: public Instruction {
private:
    std::string message;

public:
    ChatInstruction() = delete;
    ChatInstruction(std::string&& message);
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues);
    ~ChatInstruction() = default;
};

class MovementInstruction: public Instruction {
public:
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues);

};
#endif //QUANTUM_CHESS_PROJ_INSTRUCTION_H
