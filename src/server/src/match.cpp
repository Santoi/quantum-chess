#include "match.h"
#include "client_handler.h"
#include "instructions/instruction.h"
#include "instructions/exit_instruction.h"

#define MATCH_ID -1

Match::Match()
        :Thread(), accepted_clients(0) {
    this->clients.reserve(BASE_CLIENTS);
}

Match::Match(Match&& other_match)
       :Thread(std::move(other_match)), accepted_clients(other_match.accepted_clients),
        clients(std::move(other_match.clients)), listening_queues(std::move(other_match.listening_queues)),
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
    if ((int)this->clients.capacity() <= this->accepted_clients)
        this->clients.reserve(this->clients.capacity() + BASE_CLIENTS);
    this->clients.push_back(std::move(client));
    this->accepted_clients++;
}

void Match::addSingleThreadedClientToMatchAndStart(Socket&& client_socket) {
    int client_id = this->accepted_clients;
    this->addClientWithIdToListOfClients(std::move(client_socket), client_id);
    this->addClientsNickNameToRepository(client_id);
    this->clients[client_id].startSingleThreadedClient(*this);
}

void Match::addClientToMatchAndStart(Socket&& client_socket, bool threaded_match) {
    int client_id = this->accepted_clients;
    this->addClientWithIdToListOfClients(std::move(client_socket), client_id);
    this->addClientsNickNameToRepository(client_id);
    this->clients[client_id].startThreadedClient(*this, threaded_match);
}


void Match::checkAndNotifyUpdates() {
    std::shared_ptr<Instruction> instruc_ptr;
    this->match_updates_queue.pop(instruc_ptr);
    instruc_ptr->makeActionAndNotifyAllListeningQueues(this->listening_queues, this->clients);
}

void Match::run() {
    while (true)
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

void Match::pushExitInstructionToUpdatesQueue() {
    std::shared_ptr<Instruction> exit_instruc =  std::make_shared<ExitInstruction>(MATCH_ID);
    this->match_updates_queue.push(exit_instruc);
}


Match::~Match() {

}
