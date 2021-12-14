#ifndef QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
#define QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H

#include <queue>
#include <memory>
#include <condition_variable>
#include <iostream>
#include <string>

template<class T>
class BlockingQueue {
private:
  std::queue<std::shared_ptr<T>> queue;
  std::condition_variable condition_variable;
  std::mutex mutex;
  bool closed_queue;

public:
  BlockingQueue();

  BlockingQueue(BlockingQueue &&other_queue) noexcept;

  // Pushes the pointer to queue and notifies using the conditional variable
  void push(std::shared_ptr<T> ptr);

  // Wait for the queue to be non-empty, then pop
  std::shared_ptr<T> pop();

  void close();

  ~BlockingQueue() = default;
};

class BlockingQueueClosed : public std::exception {
  const std::string text;

public:
  explicit BlockingQueueClosed(std::string text_) : text(std::move(text_)) {}

  const char *what() const noexcept override {
    return text.c_str();
  }
};

template<class T>
BlockingQueue<T>::BlockingQueue()
    : queue(), condition_variable(), mutex(), closed_queue(false) {}

template<class T>
BlockingQueue<T>::BlockingQueue(BlockingQueue<T> &&other_queue) noexcept
    :queue(std::move(other_queue.queue)), condition_variable(),
     mutex(), closed_queue(other_queue.closed_queue) {
}

template<class T>
void BlockingQueue<T>::push(std::shared_ptr<T> ptr) {
  const std::lock_guard<std::mutex> u_lock(this->mutex);
  if (closed_queue)
    return;
  this->queue.push(ptr);
  this->condition_variable.notify_all();
}

template<class T>
std::shared_ptr<T> BlockingQueue<T>::pop() {
  std::unique_lock<std::mutex> u_lock(this->mutex);
  condition_variable.wait(u_lock, [&] {
    return !queue.empty() || closed_queue;
  });
  if (queue.empty() && closed_queue)
    throw BlockingQueueClosed("");
  std::shared_ptr<T> ptr = this->queue.front();
  this->queue.pop();
  return ptr;
}

template<class T>
void BlockingQueue<T>::close() {
  std::unique_lock<std::mutex> u_lock(mutex);
  closed_queue = true;
  condition_variable.notify_all();
}

#endif //QUANTUM_CHESS_PROJ_BLOCKING_QUEUE_H
