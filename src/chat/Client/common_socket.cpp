#include "common_socket.h"
#include "common_socket_closed.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#define EXITO 0
#define ERROR -1
#define MAX_QUEUE 8
#define SOCKET_NO_DISPONIBLE 0
#define INVALID_FILE_DESCRIPTOR -1
#define MAX_MENSAJE 50
#define MAX_ERROR_MESSAGE 250


Socket::Socket()
        :fd(INVALID_FILE_DESCRIPTOR) {
}

Socket::Socket(int fd_valido)
        :fd(fd_valido) {
}

Socket::Socket(Socket&& otro_socket) {
    this->fd = otro_socket.fd;
    otro_socket.fd = INVALID_FILE_DESCRIPTOR;
}

Socket Socket::createAConnectedSocket(const char* host, const char* servicio) {
    Socket socket_cliente;
    socket_cliente.inicializarYConectarCliente(host, servicio);
    return socket_cliente;
}

Socket Socket::createAListeningSocket(const char* host, const char* servicio) {
    Socket socket_servidor;
    socket_servidor.inicializarServidorConBindYListen(host, servicio);
    return socket_servidor;
}

void Socket::inicializarYConectarCliente(const char* host, const char* servicio) {
    struct addrinfo baseaddr;
    struct addrinfo* ptraddr;
    struct addrinfo* ptrAux;
    memset(&baseaddr, 0, sizeof(struct addrinfo));
    baseaddr.ai_socktype = SOCK_STREAM;
    baseaddr.ai_family = AF_UNSPEC; //Ipv4 o Ipv6
    baseaddr.ai_flags = 0; //Ningún flag ya que es un cliente
    int aux = getaddrinfo(host, servicio, &baseaddr, &ptraddr);
    if (aux != EXITO){
        fprintf(stderr, "Error: %s\n", gai_strerror(aux));
        throw std::runtime_error("");
    }
    int fdDelServidor = 0;
    bool conectados = false;
    ptrAux = ptraddr;
    while (ptrAux != nullptr && conectados == false){
        fdDelServidor = socket(ptrAux->ai_family, ptrAux->ai_socktype,
                               ptrAux->ai_protocol);
        if (fdDelServidor == ERROR) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
        } else {
            aux = connect(fdDelServidor, ptrAux->ai_addr, ptrAux->ai_addrlen);
            if (aux == ERROR) {
                fprintf(stderr, "Error: %s\n", strerror(errno));
                aux = close(fdDelServidor);
                if (aux != EXITO)
                    fprintf(stderr, "Error: %s\n", strerror(errno));
            } else {
                conectados = true;
            }
        }
        ptrAux = ptraddr->ai_next;
    }
    freeaddrinfo(ptraddr);
    if (!conectados)
        throw std::runtime_error("Error: no se pudo conectar el socket cliente.");
    this->fd = fdDelServidor;
}

void Socket::inicializarServidorConBindYListen(const char* host, const char* servicio) {
    struct addrinfo baseaddr;
    struct addrinfo* ptraddr;
    struct addrinfo* ptrAux;
    memset(&baseaddr, 0, sizeof(struct addrinfo));
    baseaddr.ai_socktype = SOCK_STREAM;
    baseaddr.ai_family = AF_UNSPEC; //Ipv4 o Ipv6
    baseaddr.ai_flags = AI_PASSIVE; //Las direcciones dadas podrán usar bind()
    //y accept()
    int aux = getaddrinfo(host, servicio, &baseaddr, &ptraddr);
    if (aux != EXITO){
        fprintf(stderr, "Error: %s\n", gai_strerror(aux));
        throw std::runtime_error("");
    }
    int fdServidor = 0;
    bool socketActivo = false;
    ptrAux = ptraddr;
    while (ptrAux != NULL && socketActivo == false){
        fdServidor = socket(ptrAux->ai_family, ptrAux->ai_socktype,
                            ptrAux->ai_protocol);
        if (fdServidor == ERROR) {
            printf("Error: %s\n", strerror(errno));
        } else {
            int val = 1;
            aux = setsockopt(fdServidor, SOL_SOCKET, SO_REUSEADDR,
                             &val, sizeof(val));
            if (aux != EXITO){
                fprintf(stderr, "Error: %s\n", strerror(errno));
                aux = close(fdServidor);
                if (aux != EXITO)
                    fprintf(stderr, "Error: %s\n", strerror(errno));
            } else {
                aux = bind(fdServidor, ptraddr->ai_addr, ptraddr->ai_addrlen);
                if (aux != EXITO){
                    fprintf(stderr, "Error: %s\n", strerror(errno));
                    aux = close(fdServidor);
                    if (aux != EXITO)
                        fprintf(stderr, "Error: %s\n", strerror(errno));
                } else {
                    socketActivo = true;
                }
            }
        }
        ptrAux = ptraddr->ai_next;
    }
    freeaddrinfo(ptraddr);
    aux = listen(fdServidor, MAX_QUEUE);
    if (aux != EXITO){
        fprintf(stderr, "Error: %s\n", strerror(errno));
        fprintf(stderr, "Error en la función listen\n");
        aux = close(fdServidor);
        if (aux != EXITO)
            fprintf(stderr, "Error: %s\n", strerror(errno));
        throw std::runtime_error("Error: no se pudo crear el socket servidor.");
    }
    this->fd = fdServidor;
}

Socket Socket::acceptSocket() {
    int fd = accept(this->fd, nullptr, nullptr);
    if (fd == ERROR)
        throw CantAcceptClientSocketError();
    Socket socket_cliente(fd);
    return socket_cliente;
}

size_t Socket::send(Packet & packet) const {
    if (fd == INVALID_FILE_DESCRIPTOR)
        throw InvalidSocketError("Error: uninitialized socket");
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

size_t Socket::receive(Packet & packet, size_t size) const {
    if (fd == INVALID_FILE_DESCRIPTOR)
        throw InvalidSocketError("Error: uninitialized socket");
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

void Socket::shutdownAndClose() {
    shutdown(this->fd, SHUT_RDWR);
    int aux = close(this->fd);
    if (aux != EXITO)
        fprintf(stderr, "Error: %s\n", strerror(errno));
}

void Socket::stopAccepting() {
    if (this->fd != INVALID_FILE_DESCRIPTOR)
        this->shutdownAndClose();
    this->fd = INVALID_FILE_DESCRIPTOR;
}

void Socket::stopCommunication() {
    this->stopAccepting();
}

Socket::~Socket() {
    if (this->fd != INVALID_FILE_DESCRIPTOR)
        this->shutdownAndClose();
}

CantAcceptClientSocketError::CantAcceptClientSocketError() noexcept {
    char str_aux[MAX_ERROR_MESSAGE];
    this->error_message = strerror_r(errno, str_aux, MAX_ERROR_MESSAGE);
}

const char* CantAcceptClientSocketError::what() const noexcept {
    return this->error_message;
}

InvalidSocketError::InvalidSocketError(const char* mensaje_de_error) noexcept {
    this->error_message = error_message;
}
const char* InvalidSocketError::what()  const noexcept {
    return this->error_message;
}
