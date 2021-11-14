#ifndef QUANTUM_CHESS_PROJ_REMOTE_CLIENTS_THREADS_H
#define QUANTUM_CHESS_PROJ_REMOTE_CLIENTS_THREADS_H

#include "thread.h"
#include <string>
#include "common_socket.h"

class RemoteClientSender {
private:
    Socket& client_socket;
    bool sender_is_active;

public:
    RemoteClientSender() = delete;
    RemoteClientSender(Socket& client_socket);
    void readFromStandardInputAndMakeAction();

protected:
    void run();

private:
    void readFromStandardInput(std::string& message);
    void makeAction(const std::string& message);
};





#endif //QUANTUM_CHESS_PROJ_REMOTE_CLIENTS_THREADS_H
