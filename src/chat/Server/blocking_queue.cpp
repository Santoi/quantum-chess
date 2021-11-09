#include "blocking_queue.h"

BlockingQueue::BlockingQueue(BlockingQueue&& other_queue)
                :queue(std::move(other_queue.queue)) {

}

void BlockingQueue::push(std::shared_ptr<Instruction> instruc_ptr) {
    this->queue.push(instruc_ptr);
}

void BlockingQueue::pop(std::shared_ptr<Instruction>& instruc_ptr) {
    instruc_ptr = this->queue.front();
    this->queue.pop();
}

