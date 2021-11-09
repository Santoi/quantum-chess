#include "match.h"
#include "client_handler.h"

Match::Match() {

}

Match::Match(Match&& other_match)
        :listening_queues(std::move(other_match.listening_queues)),
         match_updates_queue(std::move(other_match.match_updates_queue)) {
}

void Match::addClientToQueues(ClientHandler& client) {
    ThreadSafeQueue new_listening_queue;
    //maybe we can notify already existing queues that a new player is in
    this->listening_queues.push_front(std::move(new_listening_queue));
    std::list<ThreadSafeQueue>::iterator aux_pointer = this->listening_queues.begin();
    client.notifications_queue = &(*aux_pointer);
    client.updates_queue = &this->match_updates_queue;
}

void Match::checkAndNotifyUpdates() {

}


Match::~Match() {

}
