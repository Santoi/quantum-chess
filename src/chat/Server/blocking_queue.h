#ifndef QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
#define QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H

#include <queue>
#include "instructions.h"
#include <memory>
#include <condition_variable>

class BlockingQueue {
private:
    std::queue<std::shared_ptr<Instruction>> queue;
    std::condition_variable condition_variable;
    std::mutex mutex;

public:
    BlockingQueue() = default;
    BlockingQueue(BlockingQueue&& other_queue);
    void push(std::shared_ptr<Instruction> instruc_ptr);
    void pop(std::shared_ptr<Instruction>& instruc_ptr);
    ~BlockingQueue() = default;
};


#endif //QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
