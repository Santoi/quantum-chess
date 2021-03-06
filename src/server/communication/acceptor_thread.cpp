#include "acceptor_thread.h"
#include "../../common/blocking_queue.h"
#include "../../common/socket_closed.h"
#include "lobby_thread.h"
#include "match_organizer.h"

AcceptorThread::AcceptorThread(Socket &acceptor, MatchOrganizer &matches_)
    : Thread(), socket(acceptor),
      matches(matches_) {}

void AcceptorThread::run() {
  BlockingQueue<Socket> peer_queue;
  LobbyThread lobby_thread(peer_queue, matches);
  lobby_thread.start();
  try {
    while (true) {
      Socket peer = socket.accept();
      peer_queue.push(std::make_shared<Socket>(std::move(peer)));
    }
  }
  catch(const SocketClosed &e) {
    peer_queue.close();
    lobby_thread.join();
  }
}
