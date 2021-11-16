#include "acceptor_thread.h"
#include "../../common/src/blocking_queue.h"
#include "../../common/src/socket_closed.h"
#include "lobby_thread.h"
#include "matches_repository.h"

AcceptorThread::AcceptorThread(Socket &acceptor, MatchesRepository & matches_): Thread(), socket(acceptor),
                               matches(matches_){}

void AcceptorThread::run() {
    BlockingQueue<Socket> peer_queue;
    LobbyThread lobby_thread(peer_queue, matches);
    lobby_thread.start();
    try {
        while (true) {
            Socket peer = socket.acceptSocket();

            peer_queue.push(std::make_shared<Socket>(std::move(peer)));
        }
    }

    catch(const SocketClosed & e) {
        // TODO cerrar la cola
    }
    catch(const std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch(...){
        std::cerr << "Error desconocido" << std::endl;
    }

}