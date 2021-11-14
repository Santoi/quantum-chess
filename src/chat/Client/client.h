#ifndef QUANTUM_CHESS_PROJ_CLIENT_H
#define QUANTUM_CHESS_PROJ_CLIENT_H

#include "remote_clients_threads.h"
#include "common_socket.h"
#include <string>

class Client {
private:
    Socket client_socket;
    RemoteClientSender remote_sender;
    RemoteClientReceiver remote_receiver;
    std::string clients_nick_name;
public:
    Client() = delete;

    //Recibiendo un host y un servidor, se inicializa un socket cliente que se conectará al socket
    //del servidor.
    Client(const char *host, const char *servidor);

    //Se recibe por entrada estándar las operaciones a realizar. La operación define UnNombre define
    //la cola con UnNombre en el servidor. La operación push UnNombre UnMensaje pushea en la cola
    //del servidor con nombre UnNombre el mensaje UnMensaje. Por último, la operación pop UnNombre
    //hace un pop de la cola del servidor con UnNombre, y además muestra por pantalla su contenido.
    //Si no hay ningún elemento en la cola llamada UnNombre, se espera a que otro cliente agregue
    //un elemento para poder sacarlo. Para salir del ciclo de operaciones escribir por entrada
    //estándar un exit.
    void execute(bool single_threaded_client);

    //Se destruye el socket cliente.
    ~Client() = default;

private:

    void executeSingleThreadedClient();

    void executeThreadedClient();

    void setUpClientsDataInServer();

    void welcomeClientAndAskForNickName();

    void associateClientWithARunningMatch();

    int getAndPrintNumberOfAvailableGames();

    void askForMatchNumber(const int& max_games);

    void readFromStandardInput(std::string& message);
};

#endif //QUANTUM_CHESS_PROJ_CLIENT_H
