#include "common_socket.h"
#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <vector>
#include <stdexcept>
#include "common_packet.h"
#include "common_invalid_parameter_addr.h"
#include "common_socket_closed.h"

Socket::Socket(): fd(INVALID_FILE_DESCRIPTOR) {}

Socket::Socket(Socket && orig) noexcept: fd(orig.fd) {
    orig.fd = INVALID_FILE_DESCRIPTOR;
}

Socket::Socket(int fd_): fd(fd_) {}

Socket & Socket::operator=(Socket &&orig) {
    this->fd = orig.fd;
    orig.fd = INVALID_FILE_DESCRIPTOR;
    return *this;
}

Socket::~Socket() {
    shutdownAndClose();
}

void Socket::connect(const char * host, const char * port) {
    struct addrinfo * result, * ptr;
    // Se carga la estructura de direcciones.
    getAddressInfo(&result, host, port);

    // Se itera hasta que se pueda conectar.
    for (ptr = result; ptr; ptr = ptr->ai_next){
        int skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (skt != -1){
            if (::connect(skt, ptr->ai_addr, ptr->ai_addrlen)) {
                ::close(skt);
            } else {
                // Si se conecta se guarda el fd.
                fd = skt;
                break;
            }
        }
    }

    freeaddrinfo(result);

    // Si no se encontro se lanza excepcion.
    if (fd == INVALID_FILE_DESCRIPTOR)
        throw std::runtime_error("fallo al conectar al host");

    int optval = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)))
        throw std::runtime_error("fallo al configurar opciones de socket");
}

void Socket::bindAndListen(const char * port, uint8_t pend_conn) {
    struct addrinfo * result, * ptr;
    // Se carga la estructura de direcciones.
    getAddressInfo(&result, nullptr, port);

    // Se itera hasta que pueda bindear.
    for (ptr = result; ptr; ptr = ptr->ai_next) {
        int skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (skt != -1){
            int optval = 1;
            if (setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &optval,
                           sizeof(int)) < 0) {
                freeaddrinfo(result);
                throw std::runtime_error("fallo al configurar opciones "
                                         "de socket");
            }
            if (::bind(skt, result->ai_addr, result->ai_addrlen)) {
                ::close(skt);
            } else{
                // Si se pudo bindear se guarda el fd.
                fd = skt;
                break;
            }
        }
    }

    freeaddrinfo(result);
    if (fd == INVALID_FILE_DESCRIPTOR)
        throw std::runtime_error("fallo al bindear el socket");

    if (listen(fd, pend_conn))
        throw std::runtime_error("fallo al poner el puerto en escucha");
}

Socket Socket::accept() const {
    if (fd == INVALID_FILE_DESCRIPTOR)
        throw std::runtime_error("el socket tiene un fd invalido");

    // Se acepta la conexion entrante.
    int fd_peer = ::accept(fd, nullptr, nullptr);
    if (fd_peer == -1) {
        if (errno == EBADF || errno == EINVAL)
            throw SocketClosed();
        throw std::runtime_error("fallo al aceptar el peer");
    }
    return Socket(fd_peer);
}

void Socket::getAddressInfo(struct addrinfo ** result, const char * host,
                            const char * port) {
    struct addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (host == nullptr)
        hints.ai_flags = AI_PASSIVE;
    int s = getaddrinfo(host, port, &hints, result);
    if (s) {
        throw InvalidParameterAddr("direccion erronea");
    }
}

size_t Socket::send(Packet & packet) const {
    if (fd == INVALID_FILE_DESCRIPTOR)
        throw std::runtime_error("el socket tiene un fd invalido");
    packet.resetSent();
    // Mientras que quede algo pendiente de enviar se itera.
    while (packet.pendingToSentSize() > 0) {
        // Se envian los datos pendientes.
        ssize_t bytes_sent = ::send(fd, packet.getPendingToSent(),
                                    packet.pendingToSentSize(), MSG_NOSIGNAL);
        // Si no se envio nada se lanza excepcion de socket cerrado.
        if (bytes_sent == 0)
            throw SocketClosed();
        if (bytes_sent == -1) {
            if (errno == EPIPE)
                throw SocketClosed();
            throw std::runtime_error("error al enviar datos");
        }
        // Se contabiliza la cantida de bytes enviados.
        packet.addSentAmount(bytes_sent);
    }
    // Se devuelve la cantidad de bytes enviados.
    return packet.sent();
}

size_t Socket::receive(Packet & packet, size_t size) const{
    if (fd == INVALID_FILE_DESCRIPTOR)
        throw std::runtime_error("el socket tiene un fd invalido");
    // Se crea un buffer para recibir.
    std::vector<char> buffer(size, 0);
    packet.reset();
    while (packet.size() < size) {
        // Se recibe el tamanio del buffer.
        ssize_t bytes_recv = recv(fd, buffer.data(), size - packet.size(), 0);
        // Si no se recibio nada, socket cerrado. Sino error.
        if (bytes_recv == 0) {
            throw SocketClosed();
        }
        if (bytes_recv == -1) {
            if (errno == EBADF) {
                throw SocketClosed();
            }
            throw std::runtime_error("error al recibir datos");
        }
        // Se agregan los bytes recibidos al paquete.
        packet.addBytes(buffer.data(), bytes_recv);
    }
    // Se devuelven los bytes recibidos.
    return packet.size();
}

void Socket::shutdownAndClose(){
    if (fd != INVALID_FILE_DESCRIPTOR) {
        ::shutdown(fd, SHUT_RDWR);
        ::close(fd);
        fd = INVALID_FILE_DESCRIPTOR;
    }
}


