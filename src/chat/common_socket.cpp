#include "common_socket.h"
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
#define SIN_FD -1
#define MAX_MENSAJE 50
#define MAX_MENSAJE_DE_ERROR 250


Socket::Socket()
        :fd(SIN_FD) {
}

Socket::Socket(int fd_valido)
        :fd(fd_valido) {
}

Socket::Socket(Socket&& otro_socket) {
    this->fd = otro_socket.fd;
    otro_socket.fd = SIN_FD;
}

Socket Socket::crearSocketClienteYConectarlo(const char* host, const char* servicio) {
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

Socket Socket::aceptarSocket() {
    int fd = accept(this->fd, nullptr, nullptr);
    if (fd == ERROR)
        throw NoSePuedeAceptarSocketError();
    Socket socket_cliente(fd);
    return socket_cliente;
}

ssize_t Socket::enviarMensaje(const char* buffer, size_t length) {
    size_t escritos = 0;
    if (this->fd == SIN_FD)
        throw SocketNoInicializadoError("Error: un socket que no fue inicializado no puede enviar "
                                 "mensajes.");
    while (escritos < length) {
        int aux = send(this->fd, buffer + escritos,
                       length - escritos, MSG_NOSIGNAL);
        if (aux == ERROR)
            return ERROR;
        else if (aux == SOCKET_NO_DISPONIBLE)
            return escritos;
        escritos = escritos + aux;
    }
    return escritos;
}

ssize_t Socket::recibirMensaje(char* buffer, size_t length) {
    size_t leidos = 0;
    if (this->fd == SIN_FD)
        throw SocketNoInicializadoError("Error: un socket que no fue inicializado no puede recibir "
                                 "mensajes.");
    while (leidos < length) {
        int aux = recv(this->fd, buffer + leidos, length - leidos, 0);
        if (aux == ERROR)
            return ERROR;
        else if (aux == SOCKET_NO_DISPONIBLE)
            return leidos;
        leidos = leidos + aux;
    }
    return leidos;
}

void Socket::shutdownYCerrar() {
    shutdown(this->fd, SHUT_RDWR);
    int aux = close(this->fd);
    if (aux != EXITO)
        fprintf(stderr, "Error: %s\n", strerror(errno));
}

void Socket::dejarDeAceptar() {
    if (this->fd != SIN_FD)
        this->shutdownYCerrar();
    this->fd = SIN_FD;
}

Socket::~Socket() {
    if (this->fd != SIN_FD)
        this->shutdownYCerrar();
}

NoSePuedeAceptarSocketError::NoSePuedeAceptarSocketError() noexcept {
    char str_aux[MAX_MENSAJE_DE_ERROR];
    this->mensaje_de_error = strerror_r(errno, str_aux, MAX_MENSAJE_DE_ERROR);
}

const char* NoSePuedeAceptarSocketError::what() const noexcept {
    return this->mensaje_de_error;
}

SocketNoInicializadoError::SocketNoInicializadoError(const char* mensaje_de_error) noexcept {
    this->mensaje_de_error = mensaje_de_error;
}
const char* SocketNoInicializadoError::what()  const noexcept {
    return this->mensaje_de_error;
}
