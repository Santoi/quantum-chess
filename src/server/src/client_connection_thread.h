#ifndef QUANTUM_CHESS_PROJ_CLIENT_CONNECTION_THREAD_H
#define QUANTUM_CHESS_PROJ_CLIENT_CONNECTION_THREAD_H

#include <atomic>
#include "../../common/src/thread.h"
#include "../../common/src/socket.h"
#include "matches_repository.h"

class ClientConnectionThread : public Thread {
  Socket socket;
  MatchOrganizer &matches;
  std::atomic<bool> active;

public:
  explicit ClientConnectionThread(Socket &&socket_, MatchOrganizer &matches_);

  void stop();

  bool isActive() const;

private:
  void run() override;
};


#endif //QUANTUM_CHESS_PROJ_CLIENT_CONNECTION_THREAD_H
