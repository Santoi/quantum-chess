#ifndef QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
#define QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H


#include <thread>
#include "thread_safe_queue.h"
#include "common_socket.h"
#include "match.h"
#include "server_protocol.h"
#include "blocking_queue.h"
#include <memory>
class Match;

class ClientHandler {
private:
    Socket client_socket;
    int client_id;
    ServerProtocol protocol;
    BlockingQueue& notifications_queue;
    ThreadSafeQueue& updates_queue;
    std::thread receiver_thread;
    std::thread sender_thread;

public:
    ClientHandler() = delete;
    ClientHandler(Socket&& socket, BlockingQueue& notifications_queue, ThreadSafeQueue& updates_queue,
                    const int& client_id);
    ClientHandler(ClientHandler&& other_client);

    void saveIdAndAskForName(int id);
    int chooseGame(const int& max_games);
    void getClientsNickName(std::string& nick_name);
    void start();
    void startSingleThreadedClient(Match& match);

    ~ClientHandler() = default;

private:
    void executeReceiverCatchingExceptions();
    void executeReceiver();
    void executeSenderCatchingExceptions();
    void executeSender();
};



#endif //QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
