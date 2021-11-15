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

    //Creates a RemoteClientSender, saving a reference to client_socket.
    RemoteClientSender(Socket& client_socket);

    //Reads from standard input and makes corresponding action.
    void readFromStandardInputAndMakeAction();

    ~RemoteClientSender() = default;

protected:
    //Calls readFromStandardInputAndMakeAction method until it reads an "exit" from
    //standard input.
    void run();

private:
    //Saves what is in standard input into message.
    void readFromStandardInput(std::string& message);

    //Sends through the protocol the given message.
    void makeAction(const std::string& message);
};

class RemoteClientReceiver: public Thread {
private:
    Socket& client_socket;

public:
    RemoteClientReceiver() = delete;

    //Creates a RemoteClientReceiver, saving a reference to client_socket.
    RemoteClientReceiver(Socket& client_socket);

    //Asks protocol to fill a pointer to a RemoteClientInstruction derived class and
    //tells it to makeAction.
    void receiveMessage();

    ~RemoteClientReceiver() = default;

protected:
    //Calls receiveMessage until reading from socket throws exception. In a normal
    //escenario this happens because socket was shutdowned and closed by
    //RemoteClientSender.
    void run();
};





#endif //QUANTUM_CHESS_PROJ_REMOTE_CLIENTS_THREADS_H
