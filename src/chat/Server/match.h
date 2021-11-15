#ifndef QUANTUM_CHESS_PROJ_MATCH_H
#define QUANTUM_CHESS_PROJ_MATCH_H


#include <list>
#include "thread_safe_queue.h"
#include "blocking_queue.h"
#include "common_socket.h"
#include "client_handler.h"
#include "nick_names_repository.h"
#include "thread.h"

#define BASE_CLIENTS 5

class ClientHandler;

class Match: public Thread {
private:
    int accepted_clients;
    std::vector<ClientHandler> clients;
    NickNamesRepository nick_names;
    std::list<BlockingQueue> listening_queues;
    ThreadSafeQueue match_updates_queue;

public:
    //Creates a match, creating the NickNamesRepository and the ThreadSafeQueue. The client's vector
    //is also created and set with an initial capacity of BASE_CLIENTS.
    Match();

    //Moves the other match's thread, clients, listening queues and the thread safe queue to the new
    //match. The new match also copies the number of accepted clients of the other_match.
    Match(Match&& other_match);

    //Adds client to list of clients and nick names repository, and calls the client to start
    //single-threadedly
    void addSingleThreadedClientToMatchAndStart(Socket&& client_socket);

    //Adds client to list of clients and nick names repository, and calls the client to start with threads,
    //also sending the client the boolean threaded_match.
    void addClientToMatchAndStart(Socket&& client_socket, bool threaded_match);

    //Pops from updates_queue an instruction, and asks this instruction to makeActionAndNotifyAllListeningQueues.
    void checkAndNotifyUpdates();

    //Returns if the match is joinable: if the match's attribute has_active_thread is set to false,
    //false is returned. If it has an active thread, then it asks if the match is active (by calling
    //the isActive method). If the match is active then the game cannot be joined at the moment because
    //it is still executing, therefore a false is returned. If the match is not active the game can
    //be joined and a true is returned.
    bool isJoinable();

    //Iterates over the list of clients, asking each one if the respective client is active. If either
    //of them is active, then a true is returned. If neither is active, a false is returned.
    bool isActive() const;

    //Creates an ExitInstruction with MATCH_ID, and pushes it to the match_updates_queue. This is ideal
    //for when one wants to end the game's execution.
    void pushExitInstructionToUpdatesQueue();

    ~Match();

protected:
    //Calls checkAndNotifyUpdates until the match's ExitInstruction is popped and asked to
    //makeActionAndNotifyAllListeningQueues. This throws a running exception that is catched and
    //execution ends.
    void run() override;

private:
    //Creates a new ClientHandler and adds it to the client's vector (if the vector's capacity is not
    //enough, it is incremented by BASE_CLIENTS). The number of accepted clients is incremented by one.
    void addClientWithIdToListOfClients(Socket&& client_socket, const int& client_id);

    //Asks the new remote client for its nickname and saves it into the nick names repository,
    //associating it with the given client_id.
    void addClientsNickNameToRepository(const int& client_id);
};



#endif //QUANTUM_CHESS_PROJ_MATCH_H
