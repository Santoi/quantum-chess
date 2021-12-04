#include "lobby_thread.h"
#include "../../common/src/blocking_queue.h"
#include "client_handler.h"
#include "matches_repository.h"

LobbyThread::LobbyThread(BlockingQueue<Socket> &queue_,
                         MatchesRepository &matches_)
        : Thread(), queue(queue_), matches(matches_) {}

void LobbyThread::run() {
  try {
    while (true) {
      // TODO LANZAR UN HILO POR CADA CONEXION PENDIENTE. MATCHES RESPOTIROY PROTEGIDO.
      auto peer = queue.pop();
      matches.joinInactiveMatches();
      matches.addClientToMatchCreatingIfNeeded((std::move(*peer)));
    }
  }
  catch (const BlockingQueueClosed &e) {
    matches.stopMatches();
    matches.joinMatches();
  }
}