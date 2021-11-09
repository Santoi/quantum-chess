#ifndef QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
#define QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H

#include <queue>
#include "instructions.h"
#include <memory>

class BlockingQueue {
private:
    std::queue<std::shared_ptr<Instruction>> queue;

public:
    BlockingQueue() = default;
    BlockingQueue(BlockingQueue&& other_queue);
    void push(std::shared_ptr<Instruction> instruc_ptr);
    void pop(std::shared_ptr<Instruction>& instruc_ptr);
    ~BlockingQueue() = default;
};


#endif //QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
