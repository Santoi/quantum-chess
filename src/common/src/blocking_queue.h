#ifndef QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
#define QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H

#include <queue>
#include <memory>
#include <condition_variable>

template <class T>
class BlockingQueue {
private:
    std::queue<std::shared_ptr<T>> queue;
    std::condition_variable condition_variable;
    std::mutex mutex;

public:
    BlockingQueue() = default;

    //Moves other_queue.queue to this new BlockingQueue.queue. Because mutex is a non-movable object,
    //a brand new mutex is created. This means there is no relation between other_queue.mutex and
    //the new blockingqueue mutex. For this reason, it only makes sense to start using the blocking
    //queue once it is certain that it is not going to be moved anymore.
    BlockingQueue(BlockingQueue&& other_queue) noexcept ;

    //Locks the mutex, pushes the instruc_ptr to queue and notifies using the conditional variable.
    void push(std::shared_ptr<T> ptr);

    //If the queue is not empty, the instruc_ptr points to the first element in the queue, and the
    //pop method is called over the queue. If the queue is empty, a unique lock is applied to the mutex,
    //and it waits until an element is added to que queue, and the sequence described before is done.
    void pop(std::shared_ptr<T>& ptr);

    ~BlockingQueue() = default;
};

template <class T>
BlockingQueue<T>::BlockingQueue(BlockingQueue<T> && other_queue) noexcept
        :queue(std::move(other_queue.queue)), condition_variable(),
         mutex() {
}

template <class T>
void BlockingQueue<T>::push(std::shared_ptr<T> ptr) {
    const std::lock_guard<std::mutex> lock(this->mutex);
    this->queue.push(ptr);
    this->condition_variable.notify_all();
}

template <class T>
void BlockingQueue<T>::pop(std::shared_ptr<T>& ptr) {
    std::unique_lock<std::mutex> uniqueLock(this->mutex);
    while (this->queue.empty())
        this->condition_variable.wait(uniqueLock);
    ptr = this->queue.front();
    this->queue.pop();
}


#endif //QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
