#include "blocking_queue.h"

BlockingQueue::BlockingQueue(BlockingQueue&& other_queue)
                :queue(std::move(other_queue.queue)), condition_variable(),
                 mutex() {
}

void BlockingQueue::push(std::shared_ptr<Instruction> instruc_ptr) {
    const std::lock_guard<std::mutex> lock(this->mutex);
    this->queue.push(instruc_ptr);
    this->condition_variable.notify_all();
}

void BlockingQueue::pop(std::shared_ptr<Instruction>& instruc_ptr) {
    std::unique_lock<std::mutex> uniqueLock(this->mutex);
    while (this->queue.empty())
        this->condition_variable.wait(uniqueLock);
    instruc_ptr = this->queue.front();
    this->queue.pop();
}

