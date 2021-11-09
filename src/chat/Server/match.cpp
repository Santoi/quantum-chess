#include "match.h"
#include "client_handler.h"
#include "instructions.h"

Match::Match() {

}

Match::Match(Match&& other_match)
        :listening_queues(std::move(other_match.listening_queues)),
         match_updates_queue(std::move(other_match.match_updates_queue)) {
}

void Match::addClientToQueues(ClientHandler& client) {
    BlockingQueue new_listening_queue;
    //maybe we can notify already existing queues that a new player is in
    this->listening_queues.push_front(std::move(new_listening_queue));
    std::list<BlockingQueue>::iterator aux_pointer = this->listening_queues.begin();
    client.notifications_queue = &(*aux_pointer);
    client.updates_queue = &this->match_updates_queue;
}

void Match::checkAndNotifyUpdates() {
    std::shared_ptr<Instruction> instruc_ptr;
    this->match_updates_queue.pop(instruc_ptr);
    instruc_ptr->makeActionAndNotifyAllListeningQueues(this->listening_queues); //maybe game
    //and a chat as parameters?
}


Match::~Match() {

}
