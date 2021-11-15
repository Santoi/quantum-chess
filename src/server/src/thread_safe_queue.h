#ifndef TP2FINAL_THREADSAFEQUEUE_H
#define TP2FINAL_THREADSAFEQUEUE_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "instructions/instruction.h"

class ThreadSafeQueue {
    std::queue<std::shared_ptr<Instruction>> queue;
    std::mutex mutex;
    std::condition_variable condition_variable;

public:
    ThreadSafeQueue() = default;

    //Moves other_queue.queue to this new ThreadSafeQueue.queue. Because mutex is a non-movable object,
    //a brand new mutex is created. This means there is no relation between other_queue.mutex and
    //the new ThreadSafeQueue mutex. For this reason, it only makes sense to start using the thread
    //safe queue once it is certain that it is not going to be moved anymore.
    ThreadSafeQueue(ThreadSafeQueue&& other_queue);

    //Locks the mutex, pushes the instruc_ptr to queue and notifies using the conditional variable.
    void push(std::shared_ptr<Instruction> instruc_ptr);

    //If the queue is not empty, the instruc_ptr points to the first element in the queue, and the
    //pop method is called over the queue. If the queue is empty, a unique lock is applied to the mutex,
    //and it waits until an element is added to que queue, and the sequence described before is done.
    void pop(std::shared_ptr<Instruction>& instruc_ptr);

    ~ThreadSafeQueue();
};

#endif //TP2FINAL_THREADSAFEQUEUE_H
