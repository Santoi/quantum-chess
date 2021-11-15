#ifndef TP3_TALLER1_COMMON_SOCKET_CLOSED_H
#define TP3_TALLER1_COMMON_SOCKET_CLOSED_H
#include <exception>


class SocketClosed: public std::exception {
public:
    const char * what() const noexcept override {
        return "Socket is closed.";
    }
};


#endif //TP3_TALLER1_COMMON_SOCKET_CLOSED_H
