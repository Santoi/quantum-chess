#ifndef QUANTUM_CHESS_PROJ_UNIQUE_PTR_H
#define QUANTUM_CHESS_PROJ_UNIQUE_PTR_H

#include <memory>

// Template that allows creation of unique smart pointers using make_unique
// (credits to stack overflow)

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif //QUANTUM_CHESS_PROJ_UNIQUE_PTR_H
