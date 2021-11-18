#include "lobby_thread.h"
#include "../../common/src/blocking_queue.h"
#include "client_handler.h"
#include "matches_repository.h"

LobbyThread::LobbyThread(BlockingQueue<Socket> & queue_, MatchesRepository & matches_): Thread(), queue(queue_), matches(matches_) {}

void LobbyThread::run() {
    std::cout << "soy el lobby" << std::endl;
    try {
        while (true) {
            std::shared_ptr<Socket> peer;
            queue.pop(peer);
            matches.addClientToMatchCreatingIfNeeded((std::move(*peer)), true);
            matches.joinInactiveMatches();
        }
    }
    catch(const BlockingQueueClosed & e) {
        std::cout << "detengo matches" << std::endl;
        matches.stopMatches();
        matches.joinMatches();
    }
    std::cout << "chau me las pico" << std::endl;
}