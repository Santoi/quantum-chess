#ifndef QUANTUM_CHESS_PROJ_LOBBY_THREAD_H
#define QUANTUM_CHESS_PROJ_LOBBY_THREAD_H

#include "../../common/src/thread.h"
#include "../../common/src/socket.h"
#include "../../common/src/blocking_queue.h"
#include "matches_repository.h"
#include "client_connection_thread.h"

class LobbyThread : public Thread {
private:
  BlockingQueue<Socket> &queue;
  MatchOrganizer &matches;
  std::list<ClientConnectionThread> client_connection_threads;

protected:
  void run() override;

public:
  explicit LobbyThread(BlockingQueue<Socket> &queue_, MatchOrganizer &matches_);

  void stopAndJoinLobbyThreads();

  void joinInactiveLobbyThreads();
};


#endif //QUANTUM_CHESS_PROJ_LOBBY_THREAD_H
