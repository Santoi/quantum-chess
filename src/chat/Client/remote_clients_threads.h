#ifndef QUANTUM_CHESS_PROJ_REMOTE_CLIENTS_THREADS_H
#define QUANTUM_CHESS_PROJ_REMOTE_CLIENTS_THREADS_H

#include "thread.h"
#include <string>
#include "common_socket.h"

class RemoteClientSender: public Thread {
private:
    Socket& client_socket;
    bool sender_is_active;

public:
    RemoteClientSender() = delete;
    RemoteClientSender(Socket& client_socket);
    void readFromStandardInputAndMakeAction();
    ~RemoteClientSender() = default;

protected:
    void run();

private:
    void readFromStandardInput(std::string& message);
    void makeAction(const std::string& message);
};

class RemoteClientReceiver: public Thread {
private:
    Socket& client_socket;

public:
    RemoteClientReceiver() = delete;
    RemoteClientReceiver(Socket& client_socket);
    void receiveMessage();
    ~RemoteClientReceiver() = default;

protected:
    void run();
};





#endif //QUANTUM_CHESS_PROJ_REMOTE_CLIENTS_THREADS_H
