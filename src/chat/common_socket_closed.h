#ifndef TP3_TALLER1_COMMON_SOCKET_CLOSED_H
#define TP3_TALLER1_COMMON_SOCKET_CLOSED_H
#include <exception>


class SocketClosed: public std::exception {
    const char * what() const noexcept override {
        return "el socket se cerro";
    }
};


#endif //TP3_TALLER1_COMMON_SOCKET_CLOSED_H
