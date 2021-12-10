#ifndef QUANTUM_CHESS_PROJ_CLIENT_CONNECTION_THREAD_H
#define QUANTUM_CHESS_PROJ_CLIENT_CONNECTION_THREAD_H

#include <atomic>
#include "../../common/src/thread.h"
#include "../../common/src/socket.h"
#include "matches_repository.h"

// Thread that makes connection to match for a new client.
class ClientConnectionThread : public Thread {
  Socket socket;
  MatchOrganizer &matches;
  std::atomic<bool> active;

public:
  explicit ClientConnectionThread(Socket &&socket_, MatchOrganizer &matches_);

  // Stops the thread.
  void stop();

  // Returns true if thread is active.
  bool isActive() const;

private:
  // Communicates with client to add it to match.
  void run() override;
};


#endif //QUANTUM_CHESS_PROJ_CLIENT_CONNECTION_THREAD_H
