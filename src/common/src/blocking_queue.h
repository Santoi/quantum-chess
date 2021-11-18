#ifndef QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
#define QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H

#include <queue>
#include <memory>
#include <condition_variable>
#include <iostream>

template <class T>
class BlockingQueue {
private:
    std::queue<std::shared_ptr<T>> queue;
    std::condition_variable condition_variable;
    std::mutex mutex;
    bool closed_queue;

public:
    BlockingQueue();

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

    void close();

    ~BlockingQueue() = default;
};

class BlockingQueueClosed: public std::exception {
    const std::string text;

public:
    explicit BlockingQueueClosed(std::string text_): text(std::move(text_)) {}

    const char * what() const noexcept override {
        return text.c_str();
    }
};

template<class T>
BlockingQueue<T>::BlockingQueue(): queue(), condition_variable(), mutex(), closed_queue(false){}

template <class T>
BlockingQueue<T>::BlockingQueue(BlockingQueue<T> && other_queue) noexcept
        :queue(std::move(other_queue.queue)), condition_variable(),
         mutex(), closed_queue(other_queue.closed_queue) {
}

template <class T>
void BlockingQueue<T>::push(std::shared_ptr<T> ptr) {
    const std::lock_guard<std::mutex> u_lock(this->mutex);
    if (closed_queue)
        return;
    this->queue.push(ptr);
    this->condition_variable.notify_all();
}

template <class T>
void BlockingQueue<T>::pop(std::shared_ptr<T>& ptr) {
    std::unique_lock<std::mutex> u_lock(this->mutex);
    condition_variable.wait(u_lock, [&] {
        return !queue.empty() || closed_queue;
    });
    if (queue.empty() && closed_queue) {
        std::cout << "salgo por closed queue" << std::endl;
        throw BlockingQueueClosed("");
    }
    ptr = this->queue.front();
    this->queue.pop();
}

template <class T>
void BlockingQueue<T>::close(){
    std::unique_lock<std::mutex> u_lock(mutex);
    // Se marca la cola como cerrada.
    closed_queue = true;
    // Se notifica a todos los hilos que se cerro la cola.
    condition_variable.notify_all();
}

#endif //QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
