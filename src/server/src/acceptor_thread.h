#ifndef QUANTUM_CHESS_PROJ_ACCEPTOR_THREAD_H
#define QUANTUM_CHESS_PROJ_ACCEPTOR_THREAD_H

#include "../../common/src/thread.h"
#include "../../common/src/socket.h"
#include "matches_repository.h"

class AcceptorThread: public Thread {
private:
    Socket & socket;
    MatchesRepository & matches;

protected:
    void run() override;

public:
    explicit AcceptorThread(Socket & acceptor, MatchesRepository & matches_);
};


#endif //QUANTUM_CHESS_PROJ_ACCEPTOR_THREAD_H
