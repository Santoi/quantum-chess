#include "match.h"
#include "client_handler.h"
#include "instructions.h"

Match::Match()
        :accepted_clients(0) {
}
//Match& Match::operator=(Match&& other_match) {
    /*this->accepted_clients = other_match.accepted_clients;
    this->clients = std::move(other_match.clients);
    this->listening_queues = std::move(other_match.listening_queues);
    this->match_updates_queue = std::move(other_match.match_updates_queue);
    return *this;*/
  //  this
//}


/*
Match& Match::operator=(const Match& other_match) {

}*/

Match::Match(Match&& other_match)
       :accepted_clients(other_match.accepted_clients), clients(std::move(other_match.clients)),
        listening_queues(std::move(other_match.listening_queues)),
        match_updates_queue(std::move(other_match.match_updates_queue)) {
}

void Match::addClientsNickNameToRepository(const int& client_id) {
    std::string nick_name;
    this->clients[client_id].getClientsNickName(nick_name);
    this->nick_names.saveNickNameRelatedToId(std::move(nick_name), client_id);
}

void Match::addClientWithIdToListOfClients(Socket&& client_socket, const int& client_id) {
    BlockingQueue new_listening_queue;
    this->listening_queues.push_front(std::move(new_listening_queue));
    ClientHandler client(std::move(client_socket), this->listening_queues.front(),
                         this->match_updates_queue, client_id, this->nick_names);
    this->clients.push_back(std::move(client));
    this->accepted_clients++;
}

void Match::addSingleThreadedClientToMatchAndStart(Socket&& client_socket) {
    int client_id = this->accepted_clients;
    this->addClientWithIdToListOfClients(std::move(client_socket), client_id);
    this->addClientsNickNameToRepository(client_id);
    this->clients[client_id].startSingleThreadedClient(*this);
}

void Match::addClientToMatchAndStart(Socket&& client_socket) {
    int client_id = this->accepted_clients;
    this->addClientWithIdToListOfClients(std::move(client_socket), client_id);
    this->addClientsNickNameToRepository(client_id);
    this->clients[client_id].startThreadedClientWithoutMatchThread(*this);
}

/*
void Match::addClientToQueues(ClientHandler& client) {
    BlockingQueue new_listening_queue;
    //maybe we can notify already existing queues that a new player is in
    this->listening_queues.push_front(std::move(new_listening_queue));
    std::list<BlockingQueue>::iterator aux_pointer = this->listening_queues.begin();
    client.notifications_queue = &(*aux_pointer);
    client.updates_queue = &this->match_updates_queue;
}*/

void Match::checkAndNotifyUpdates() {
    std::shared_ptr<Instruction> instruc_ptr;
    this->match_updates_queue.pop(instruc_ptr);
    instruc_ptr->makeActionAndNotifyAllListeningQueues(this->listening_queues, this->clients);
    //maybe game and a chat as parameters?
}

void Match::run() {
    for (int i = 0; i < 10; i++)
        checkAndNotifyUpdates();
}

bool Match::isJoinable() {
    if (!this->has_active_thread) //Match is not an alive object
        return false;
    return !(this->isActive()); //If it is active then match is not joinable. If its not, then match
                                //is joinable
}

bool Match::isActive() const {
    std::vector<ClientHandler>::const_iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); it++) {
        if (it->isActive())
            return true;
    }
    return false;
}

Match::~Match() {

}
