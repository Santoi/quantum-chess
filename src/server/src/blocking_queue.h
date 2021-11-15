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

    //Moves other_queue.queue to this new BlockingQueue.queue. Because mutex is a non-movable object,
    //a brand new mutex is created. This means there is no relation between other_queue.mutex and
    //the new blockingqueue mutex. For this reason, it only makes sense to start using the blocking
    //queue once it is certain that it is not going to be moved anymore.
    BlockingQueue(BlockingQueue&& other_queue);

    //Locks the mutex, pushes the instruc_ptr to queue and notifies using the conditional variable.
    void push(std::shared_ptr<Instruction> instruc_ptr);

    //If the queue is not empty, the instruc_ptr points to the first element in the queue, and the
    //pop method is called over the queue. If the queue is empty, a unique lock is applied to the mutex,
    //and it waits until an element is added to que queue, and the sequence described before is done.
    void pop(std::shared_ptr<Instruction>& instruc_ptr);

    ~BlockingQueue() = default;
};


#endif //QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
