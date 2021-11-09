#ifndef QUANTUM_CHESS_PROJ_SERVER_H
#define QUANTUM_CHESS_PROJ_SERVER_H

#include <list>
#include "common_socket.h"
#include "client_handler.h"
class Server {
private:
    Socket acceptor_socket;

public:
    Server() = delete;

    Server(const char* host, const char* service);

    void execute(bool one_thread_only);

    ~Server() = default;

private:

    void executeSingleThreadedServer();

    void executeServerWithThreads();

    void executeAcceptorThread();

    void createClientAndAddToList(std::list<ClientHandler>& clients);

  //  void ejecutarSoloHiloMain();

    //void ejecutarConHilos();

    //void ejecutarHiloAceptador();

    //int agregarClienteALista(std::list<ManejaCliente>& hilos_clientes);
};



#endif //QUANTUM_CHESS_PROJ_SERVER_H
