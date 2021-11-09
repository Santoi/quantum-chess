#ifndef QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
#define QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H


#include <thread>
#include "thread_safe_queue.h"
#include "common_socket.h"
#include "match.h"

class Match;

class ClientHandler {
private:
    Socket client_socket;
    ThreadSafeQueue* notifications_queue;
    ThreadSafeQueue* updates_queue;
    std::thread receiver_thread;
    std::thread sender_thread;

public:
    ClientHandler() = delete;
    ClientHandler(Socket&& socket);
    ClientHandler(ClientHandler&& other_client);
    friend void Match::addClientToQueues(ClientHandler& client);
    int chooseGame();
    ~ClientHandler() = default;
};



#endif //QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
