#ifndef QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
#define QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H


#include <thread>
#include "thread_safe_queue.h"
#include "../../common/src/socket.h"
#include "match.h"
#include "server_protocol.h"
#include "../../common/src/blocking_queue.h"
#include "nick_names_repository.h"
#include <memory>
#include "clients_threads.h"

class Match;

class ClientHandler {
private:
    Socket client_socket;
    ClientHandlersReceiver client_receiver;
    ClientHandlersSender client_sender;
    bool client_is_active;

public:
    ClientHandler() = delete;

    //A ClientHandler is created, moving and storing the given socket. A ClientHandlersReceiver and
    //ClientHandlersSender are also created and saved. The boolean client_is_active is set to true.
    ClientHandler(Socket&& socket, BlockingQueue<Instruction>& notifications_queue, ThreadSafeQueue& updates_queue,
                    const int& client_id, const NickNamesRepository& nick_names);

    //Creates a new ClientHandler by moving the other_client's socket to the new handler, and creating
    //the new receivers and senders respectively. The new handler saves the other_client boolean
    //client_is_active.
    ClientHandler(ClientHandler&& other_client);

    //Sends to the socket, using the protocol, the number of games running. It then receives from the
    //socket the number of the chosen game, returning it.
    int chooseGame(const int& max_games);

    //Receives from the socket the client's nick name.
    void getClientsNickName(std::string& nick_name);

    //Starts the execution of a single threaded client. Receives instruction from client receiver,
    //asks match to check and notify updates, and tells client sender to send instruction. This
    //happens until the remote client closes its socket. After that, the client receiver pushes the
    //exit instruction, asks match to check and notify updates, and asks the client sender to pop and
    //send the exit instruction, throwing an exception and getting out of the execution cycle.
    //At the end, client_is_active is set to false.
    void startSingleThreadedClient(Match& match);

    //Starts ClientHandler's threads by calling the private start method. If match has its own thread
    //(threaded_match is true), then the function ends. If threaded_match is false, while the boolean
    //client_is_active is true, the match is asked to check updates coming from the receiver's thread
    //and notify updates to the sender's thread.
    void startThreadedClient(Match& match, bool threaded_match);

    //Joins (if joinable) both the handler's receiver and sender threads. Object's boolean
    //client_is_active is set to true.
    void join();

    //Returns client_is_active boolean.
    bool isActive() const;

    ~ClientHandler() = default;

private:
    //Starts both ClientHandlersSender and ClientHandlersReceiver threads.
    void start();

};



#endif //QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
