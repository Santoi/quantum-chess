#ifndef TP3_TALLER1_SOCKET_H
#define TP3_TALLER1_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <exception>

#include "packet.h"

class Socket {
private:
    int fd;

public:
    //A new socket is created by assigning other_socket's fd to new socket's fd. Other socket's fd
    //is set to be a invalid_fd.
    Socket(Socket&& other_socket);

    //Creates and returns a client socket using the host and service provided, connecting it
    //accordingly
    static Socket createAConnectedSocket(const char* host, const char* service);

    //Creates a server socket using the host and service provided. A bind and a listen is applied to
    //the new socket, leaving it on a valid state for accepting client sockets. The server socket is
    //returned.
    static Socket createAListeningSocket(const char* host, const char* service);

    //A client socket is created from a server socket (initialized previously with class
    //method createAListeningSocket. If there is an error accepting the client socket, the exception
    //CantAcceptClientSocketError is thrown, to which one can ask what the error was. The client
    //socket is returned.
    Socket acceptSocket();

    //Sends the contents of the packet.
    size_t send(Packet & packet) const;

    //Receives size bytes from socket, storing them in the given packet.
    size_t receive(Packet & packet, size_t size) const;

    //The given socket is shutdowned and closed.
    void shutdownAndClose();

    //Sockets resources are freed. If socket has an valid fd, it is shutdowned and closed. If it is
    //an invalid fd, nothing is done.
    ~Socket();

private:
    //A socket with an invalid fd is created.
    Socket();

    //A socket is created with a valid file descriptor passed by parameter.
    explicit Socket(int valid_fd);

    //client socket is initialized using the host and service parameters and it is connected to the
    //appropiate server socket.
    void inicializarYConectarCliente(const char* host, const char* service);

    //Server socket is initialized, and a bind and listen is applied to it, leaving it on a valid
    //state so it can be used to accept client sockets.
    void inicializarServidorConBindYListen(const char* host, const char* service);
};

class CantAcceptClientSocketError: public std::exception {
private:
    char* error_message;

public:
    //An error is created, saving in the error_message what is in errno.
    CantAcceptClientSocketError() noexcept;

    //Returns a pointer to the buffer containing the saved error message.
    const char* what()  const noexcept;

    ~CantAcceptClientSocketError() override = default;
};

class InvalidSocketError: public std::exception {
private:
    const char* error_message;

public:
    //A new error is created, saving the error message passed to the function.
    explicit InvalidSocketError(const char* error_message) noexcept;

    //Returns a pointer to the buffer containing the error message.
    const char* what()  const noexcept;

    ~InvalidSocketError() = default;
};


#endif //TP3_TALLER1_SOCKET_H
