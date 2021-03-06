#ifndef QUANTUM_CHESS_PROJ_LOBBY_THREAD_H
#define QUANTUM_CHESS_PROJ_LOBBY_THREAD_H

#include "../../common/thread.h"
#include "../../common/socket.h"
#include "../../common/blocking_queue.h"
#include "match_organizer.h"
#include "client_connection_thread.h"
#include <list>

// Thread that push sockets of new clients from a blocking queue and creates
// and handles threads of clients connections. It also handles closed matches.
class LobbyThread : public Thread {
private:
  BlockingQueue<Socket> &queue;
  MatchOrganizer &matches;
  std::list<ClientConnectionThread> client_connection_threads;

private:
  // Stop all client connection threads and join them.
  void stopAndJoinClientConnectionThreads();

  // Checks what client connection threads finished, joins and deletes them.
  void joinInactiveClientConnectionThreads();

protected:
  // Pushes from a blocking queue with new client sockets, creates individual
  // connection threads for new connections and stops and joins them. Also
  // delete and joins finished matches.
  void run() override;

public:
  explicit LobbyThread(BlockingQueue<Socket> &queue_, MatchOrganizer &matches_);
};


#endif //QUANTUM_CHESS_PROJ_LOBBY_THREAD_H
