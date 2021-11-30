#ifndef QUANTUM_CHESS_PROJ_MESSAGE_CONTAINER_H
#define QUANTUM_CHESS_PROJ_MESSAGE_CONTAINER_H

#include <list>
#include <mutex>

template<class T>
class MessageContainer {
  std::list<T> messages;
  size_t max;
  std::mutex mutex;

public:
  explicit MessageContainer(size_t max_size);

  void add(T &&new_);

  std::list<T> getList();
};

template<class T>
MessageContainer<T>::MessageContainer(size_t max_size): max(max_size) {}

template<class T>
void MessageContainer<T>::add(T &&new_) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (messages.size() == max)
    messages.erase(messages.begin());
  messages.push_back(std::move(new_));
}

template<class T>
std::list<T> MessageContainer<T>::getList() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return messages;
}


#endif //QUANTUM_CHESS_PROJ_MESSAGE_CONTAINER_H
