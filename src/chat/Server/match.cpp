#include "match.h"
#include "client_handler.h"
#include "instructions.h"

Match::Match()
        :accepted_clients(0) {
}

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
    instruc_ptr->makeActionAndNotifyAllListeningQueues(this->listening_queues); //maybe game
    //and a chat as parameters?
}


Match::~Match() {

}
