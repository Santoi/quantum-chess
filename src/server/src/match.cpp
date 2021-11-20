#include "match.h"
#include "client_handler.h"
#include "quantum_chess/board.h"
#include "instructions/instruction.h"
#include "instructions/exit_instruction.h"
#include "instructions/load_board_instruction.h"

#define MATCH_ID -1

// TODO AVeriguar donde arranca match.

Match::Match()
        :Thread(), board(), clients(), listening_queues(), match_updates_queue() {
}

Match::Match(Match&& other_match)
       :Thread(std::move(other_match)),
        clients(std::move(other_match.clients)), listening_queues(std::move(other_match.listening_queues)),
        match_updates_queue(std::move(other_match.match_updates_queue)), board(std::move(other_match.board)) {
}

ClientData Match::askClientData(Socket & socket, uint16_t client_id){
    ServerProtocol protocol;
    std::string nickname;
    protocol.getNickName(socket, nickname);
    ClientData client_data(client_id, nickname, true, false);
    return client_data;
}

// TODO refactor.
void Match::addClientsNickNameToRepository(uint16_t client_id) {
    std::string nick_name;
    // TODO aca pedir todos los datos.
    this->clients.at(client_id).getClientsNickName(nick_name);
    ClientData new_client_data(client_id, nick_name, true, false);

}
// TODO refactor.
void Match::addClientWithIdToListOfClients(Socket&& client_socket, ClientData &client_data) {
    BlockingQueue<Instruction> new_listening_queue;
    uint16_t client_id = client_data.getId();
    listening_queues.insert(std::make_pair(client_id, std::move(new_listening_queue)));
    ClientHandler client(std::move(client_socket), this->listening_queues.at(client_id),
                         this->match_updates_queue,
                         client_data);
    clients.insert(std::make_pair(client_id, std::move(client)));
}
/*
void Match::addSingleThreadedClientToMatchAndStart(Socket&& client_socket) {
    uint16_t client_id = this->accepted_clients;
    this->addClientWithIdToListOfClients(std::move(client_socket), client_id);
    this->addClientsNickNameToRepository(client_id);
    this->clients.at(client_id).startSingleThreadedClient(*this);
}*/

void Match::addClientToMatch(Socket &&client_socket, bool threaded_match,
                             uint16_t client_id) {
    ClientData client_data = askClientData(client_socket, client_id);
    this->addClientWithIdToListOfClients(std::move(client_socket), client_data);
    this->clients.at(client_id).startThreadedClient(*this, threaded_match);
    LoadBoardInstruction instruction;
    match_updates_queue.push(std::make_shared<LoadBoardInstruction>(instruction));
}

void Match::stop() {
    match_updates_queue.close();
}

void Match::checkAndNotifyUpdates() {
    std::shared_ptr<Instruction> instruc_ptr;
    this->match_updates_queue.pop(instruc_ptr);
    instruc_ptr->makeActionAndNotifyAllListeningQueues(this->listening_queues, this->clients, this->board, match_updates_queue);
}

void Match::run() {
    board.load();
    try {
        while (true)
            checkAndNotifyUpdates();
    }
    catch (const BlockingQueueClosed& error) {
        for (auto & client: clients) {
            client.second.stop();
            client.second.join();
        }
    }
}

bool Match::hasActiveClients() const {
    return clients.size() > 0;
}
/*
void Match::pushExitInstructionToUpdatesQueue() {
    std::shared_ptr<Instruction> exit_instruc =  std::make_shared<ExitInstruction>(MATCH_ID);
    this->match_updates_queue.push(exit_instruc);
}*/

std::vector<const ClientData*> Match::getClientsData() const {
    std::vector<const ClientData*> output;
    output.reserve(clients.size());
    for (auto & client: clients)
        output.push_back(&(client.second.getData()));
    return output;
}


/*
 *    std::vector<Position> positions;
    std::vector<char> characters;
    board.loadVectors(characters, positions);
    LoadBoardInstruction instr(std::move(characters), std::move(positions));
    instr.makeActionAndNotifyAllListeningQueues(listening_queues, clients, board);
 */
