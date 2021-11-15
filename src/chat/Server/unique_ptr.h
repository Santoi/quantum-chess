#ifndef QUANTUM_CHESS_PROJ_UNIQUE_PTR_H
#define QUANTUM_CHESS_PROJ_UNIQUE_PTR_H

#include <memory>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif //QUANTUM_CHESS_PROJ_UNIQUE_PTR_H
