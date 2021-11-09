#include "thread_safe_queue.h"
#include <utility>


ThreadSafeQueue::ThreadSafeQueue() {
}

ThreadSafeQueue::ThreadSafeQueue(ThreadSafeQueue&& other_queue)
                :queue(std::move(other_queue.queue)), mutex(), condition_variable() {

}


void ThreadSafeQueue::push(std::shared_ptr<Instruction> instruc_ptr) {
    const std::lock_guard<std::mutex> lock(this->mutex);
    this->queue.push(std::move(instruc_ptr));
    this->condition_variable.notify_all();
}

void ThreadSafeQueue::pop(std::shared_ptr<Instruction>& instruc_ptr) {
    std::unique_lock<std::mutex> uniqueLock(this->mutex);
    while (this->queue.empty())
        this->condition_variable.wait(uniqueLock);
    instruc_ptr = this->queue.front();
    this->queue.pop();
}

ThreadSafeQueue::~ThreadSafeQueue() {
}
