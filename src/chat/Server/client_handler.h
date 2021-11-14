#ifndef QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
#define QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H


#include <thread>
#include "thread_safe_queue.h"
#include "common_socket.h"
#include "match.h"
#include "server_protocol.h"
#include "blocking_queue.h"
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
    ClientHandler(Socket&& socket, BlockingQueue& notifications_queue, ThreadSafeQueue& updates_queue,
                    const int& client_id, const NickNamesRepository& nick_names);
    ClientHandler(ClientHandler&& other_client);
    void saveIdAndAskForName(int id);
    int chooseGame(const int& max_games);
    void getClientsNickName(std::string& nick_name);
    void start();
    void startSingleThreadedClient(Match& match);
    void startThreadedClient(Match& match, bool threaded_match);
    void join();
    bool isActive() const;
    ~ClientHandler() = default;

};



#endif //QUANTUM_CHESS_PROJ_CLIENT_HANDLER_H
