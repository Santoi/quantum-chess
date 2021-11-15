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

    //Creates a new client receiver, saving the references to the socket and updates_queue passed in
    //the function parameters, and saves a copy of the client_id.
    ClientHandlersReceiver(Socket& socket, const int& client_id, ThreadSafeQueue& updates_queue);

    //Saves the other_receiver's ThreadSafeQueue reference in new client receiver, and
    //copies the other's client_id to new receivers's client_id. It receives a reference
    //to a valid socket.
    ClientHandlersReceiver(ClientHandlersReceiver&& other_receiver, Socket& socket);

    //Receives from socket, following the protocol, the new instruction and pushes it to the
    //updates_queue.
    void receiveInstructionAndPushToQueue();

    //Pushes to updates_queue the client's exit instruction.
    void pushToQueueExitInstruction();

    ~ClientHandlersReceiver() = default;

protected:
    //While the remote client socket is closed, the receiveInstructionAndPushToQueue method is called.
    //After the remote client socket is closed, the client's exit instruction is pushed to queue by
    //calling pushToQueueExitInstruction.
    void run() override;
};

class ClientHandlersSender: public Thread {
private:
    Socket& client_socket;
    const int client_id;
    BlockingQueue& notifications_queue;
    const NickNamesRepository& nick_names;

public:
    ClientHandlersSender() = delete;
    //Creates a new client sender, saving the references to the socket, notifications_queue and
    //nick_names repository passed in the function parameters, and saves a copy of the
    //client_id.
    ClientHandlersSender(Socket& socket, BlockingQueue& notifications_queue, const int& client_id, const NickNamesRepository& nick_names);

    //Saves the other_receiver's BlockingQueue, NickNamesRepository references in new client
    //sender, and copies the other's client_id to new receivers's client_id. It receives a
    //reference to the valid socket.
    ClientHandlersSender(ClientHandlersSender&& other_sender, Socket& socket);

    //Pops from the notifications_queue an instruction and sends, following the protocol, the
    //necessary information to the remote client's socket.
    void popFromQueueAndSendInstruction();

    ~ClientHandlersSender() = default;

protected:
    //Calls popFromQueueAndSendInstruction until the ExitInstruction of the corresponding client
    //throws the runtime exception.
    void run() override;
};




#endif //QUANTUM_CHESS_PROJ_CLIENTS_THREADS_H
