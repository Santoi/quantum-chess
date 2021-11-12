#ifndef QUANTUM_CHESS_PROJ_CLIENTS_THREADS_H
#define QUANTUM_CHESS_PROJ_CLIENTS_THREADS_H

#include "thread.h"
#include "common_socket.h"
#include "thread_safe_queue.h"
#include "blocking_queue.h"

class ClientHandlersReceiver: public Thread {
private:
    Socket& client_socket;
    const int client_id;
    ThreadSafeQueue& updates_queue;

public:
    ClientHandlersReceiver() = delete;
    ClientHandlersReceiver(ClientHandlersReceiver&& otherReceiver, Socket& socket);
    ClientHandlersReceiver(Socket& socket, const int& client_id, ThreadSafeQueue& updates_queue);
    ~ClientHandlersReceiver() = default;

protected:
    void run();
};

class ClientHandlersSender: public Thread {
private:
    Socket& client_socket;
    BlockingQueue& notifications_queue;
    const NickNamesRepository& nick_names;

public:
    ClientHandlersSender() = delete;
    ClientHandlersSender(ClientHandlersSender&& otherSender, Socket& socket);
    ClientHandlersSender(Socket& socket, BlockingQueue& notifications_queue, const NickNamesRepository& nick_names);
    ~ClientHandlersSender() = default;

protected:
    void run();
};




#endif //QUANTUM_CHESS_PROJ_CLIENTS_THREADS_H