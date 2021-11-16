#ifndef QUANTUM_CHESS_PROJ_CLIENT_H
#define QUANTUM_CHESS_PROJ_CLIENT_H

#include "remote_clients_threads.h"
#include "../../common/src/socket.h"
#include "../../common/src/blocking_queue.h"
#include "remote_client_instructions.h"
#include <string>

class Client {
private:
    Socket client_socket;
    BlockingQueue<RemoteClientInstruction> received;
    BlockingQueue<RemoteClientInstruction> send;
    RemoteClientSender remote_sender;
    RemoteClientReceiver remote_receiver;
    std::string clients_nick_name;
    AsciiBoard board;

public:
    Client() = delete;

    //Giving the host and server parameters, a client is created along with its socket. RemoteClientSender
    // and RemoteClientReceiver are also created saving a reference to the socket.
    Client(const char* host, const char* server);

    //Executes client. To stop execution, type "exit" to stdin. If single_threaded_client is true,
    //then the client is single threaded and the work sequence is: 1. send instruction to server and
    //2. receive instruction from server, until the client decides to exit. If single_threaded_client is
    //false, then both remote_sender and remote_receiver threads are started, and client can receive
    //and send instruction without any synchronization. When the command "exit" is read, both sender and
    //receiver threads are joined and the execution is finished.
    void execute(bool single_threaded_client);

    //Se destruye el socket cliente.
    ~Client() = default;

private:
    //Executes single threaded client.
    void executeSingleThreadedClient();

    //Executes threaded client.
    void executeThreadedClient();

    //Sets up login data in server: this is, the client's nick name and the match the client wants to
    //play in / watch.
    void setUpClientsDataInServer();

    //Prints to stdout a welcoming message and asks client to type wanted nick name. It saves the
    //given nick name in the client's nick_name attribute.
    void welcomeClientAndAskForNickName();

    //Prints to stdout the number of available matches, and asks the client if them wants to join an
    //existing match or if them wants to create a new match. The chosen match number is sent to the
    //server.
    void associateClientWithARunningMatch();

    //Prints the number of available matches.
    int getAndPrintNumberOfAvailableGames();

    //Asks the client to write to stdin the chosen match.
    void askForMatchNumber(const int& max_games);

    //Saves what is in standard input into message..
    void readFromStandardInput(std::string& message);

    bool readCommand();
};

#endif //QUANTUM_CHESS_PROJ_CLIENT_H
