#include "lobby_thread.h"
#include "../../common/src/blocking_queue.h"
#include "client_handler.h"
#include "matches_repository.h"

LobbyThread::LobbyThread(BlockingQueue<Socket> &queue_,
                         MatchOrganizer &matches_)
        : Thread(), queue(queue_), matches(matches_),
          client_connection_threads() {}

void LobbyThread::run() {
  try {
    while (true) {
      auto peer = queue.pop();
      matches.joinInactiveMatches();
      joinInactiveClientConnectionThreads();
      client_connection_threads.emplace_back(std::move(*peer), matches);
      client_connection_threads.back().start();
    }
  }
  catch (const BlockingQueueClosed &e) {
    matches.stopMatches();
    matches.joinMatches();
    stopAndJoinClientConnectionThreads();
  }
}

void LobbyThread::stopAndJoinClientConnectionThreads() {
  for (auto &thread: client_connection_threads) {
    thread.stop();
    thread.join();
  }
}

void LobbyThread::joinInactiveClientConnectionThreads() {
  for (auto it = client_connection_threads.begin();
       it != client_connection_threads.end();) {
    if (!it->isActive()) {
      it->join();
      it = client_connection_threads.erase(it);
    } else {
      ++it;
    }
  }
}
