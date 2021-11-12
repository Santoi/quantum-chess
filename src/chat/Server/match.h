#ifndef QUANTUM_CHESS_PROJ_MATCH_H
#define QUANTUM_CHESS_PROJ_MATCH_H


#include <list>
#include "thread_safe_queue.h"
#include "blocking_queue.h"
#include "common_socket.h"
#include "client_handler.h"
#include "nick_names_repository.h"

class ClientHandler;

class Match {
private:
    int accepted_clients;
    std::vector<ClientHandler> clients;
    NickNamesRepository nick_names;
    std::list<BlockingQueue> listening_queues;
    ThreadSafeQueue match_updates_queue;

public:
    Match();
    Match(Match&& other_match);
    void addSingleThreadedClientToMatchAndStart(Socket&& client_socket);
    void addClientToMatchAndStart(Socket&& client_socket);
    //void addClientToMatchAndBeginExcecution(Socket&& client_socket);
    //void addClientToQueues(ClientHandler& client);
    void checkAndNotifyUpdates();
    ~Match();

private:
    void addClientWithIdToListOfClients(Socket&& client_socket, const int& client_id);
    void addClientsNickNameToRepository(const int& client);
};



#endif //QUANTUM_CHESS_PROJ_MATCH_H
