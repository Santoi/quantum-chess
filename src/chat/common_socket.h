#ifndef TP3_TALLER1_SOCKET_H
#define TP3_TALLER1_SOCKET_H

#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "common_packet.h"

#define INVALID_FILE_DESCRIPTOR -1

// Clase wrapper de socket.
class Socket {
    int fd;

    explicit Socket(int fd);

    void getAddressInfo(struct addrinfo ** result, const char * host,
                        const char * port);

public:
    Socket();

    Socket(const Socket & orig) = delete;

    // Constructor por movimiento.
    Socket(Socket && orig) noexcept;

    Socket & operator=(const Socket & orig) = delete;

    // Operador asignacion por movimiento.
    Socket & operator=(Socket && orig);

    ~Socket();

    /* Permite conectar al host y puerto pasado por parametro.
     * Pre:
     *  -host y port deben apuntar a posiciones de memoria validas. */
    void connect(const char * host, const char * port);

    /* Permite bindear el socket y dejarlo en escucha en el puerto
     * pasado como parametro. Se le pasa la cantidad de conexiones
     * que se permitira tener pendientes.
     * Pre:
     *  -port debe apuntar a una posicion de memoria valida. */
    void bindAndListen(const char *port, uint8_t pend_conn);

    /* Acepta una conexion entrante.
     * Pre:
     *  - el Socket debe estar bindeado anteriormente. */
    Socket accept() const;

    // Envia un paquete.
    size_t send(Packet & packet) const;

    // Recibe un paquete de size bytes.
    size_t receive(Packet & packet, size_t size) const;

    // Hace un shutdown y un close del socket.
    void shutdownAndClose();
};


#endif //TP3_TALLER1_SOCKET_H
