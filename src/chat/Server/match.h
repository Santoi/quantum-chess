#ifndef QUANTUM_CHESS_PROJ_MATCH_H
#define QUANTUM_CHESS_PROJ_MATCH_H


#include <list>
#include "thread_safe_queue.h"

class ClientHandler;

class Match {
private:
    std::list<ThreadSafeQueue> listening_queues;
    ThreadSafeQueue match_updates_queue;

public:
    Match();
    Match(Match&& other_match);
    void addClientToQueues(ClientHandler& client);
    void checkAndNotifyUpdates();
    ~Match();
};



#endif //QUANTUM_CHESS_PROJ_MATCH_H
