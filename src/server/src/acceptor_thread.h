#ifndef QUANTUM_CHESS_PROJ_ACCEPTOR_THREAD_H
#define QUANTUM_CHESS_PROJ_ACCEPTOR_THREAD_H

#include "../../common/src/thread.h"
#include "../../common/src/socket.h"
#include "matches_repository.h"

// Thread that accepts new client connections.
class AcceptorThread : public Thread {
private:
  Socket &socket;
  MatchOrganizer &matches;

protected:
  // Accepts new sockets and push them into a queue to be read by lobby thread.
  void run() override;

public:
  AcceptorThread(Socket &acceptor, MatchOrganizer &matches_);
};


#endif //QUANTUM_CHESS_PROJ_ACCEPTOR_THREAD_H
