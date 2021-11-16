#ifndef QUANTUM_CHESS_PROJ_LOBBY_THREAD_H
#define QUANTUM_CHESS_PROJ_LOBBY_THREAD_H

#include "../../common/src/thread.h"
#include "../../common/src/socket.h"
#include "../../common/src/blocking_queue.h"
#include "matches_repository.h"

#define MAX_GAMES 5

class LobbyThread: public Thread {
private:
    BlockingQueue<Socket> & queue;
    MatchesRepository & matches;

protected:
    void run() override;

public:
    LobbyThread(BlockingQueue<Socket> & queue_, MatchesRepository & matches);
};


#endif //QUANTUM_CHESS_PROJ_LOBBY_THREAD_H
