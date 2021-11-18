#include "match.h"
#include "client_handler.h"
#include "quantum_chess/board.h"
#include "instructions/instruction.h"
#include "instructions/exit_instruction.h"
#include "instructions/load_board_instruction.h"

#define MATCH_ID -1

// TODO AVeriguar donde arranca match.

Match::Match()
        :Thread(), accepted_clients(0), board() {
}

Match::Match(Match&& other_match)
       :Thread(std::move(other_match)), accepted_clients(other_match.accepted_clients),
        clients(std::move(other_match.clients)), listening_queues(std::move(other_match.listening_queues)),
        match_updates_queue(std::move(other_match.match_updates_queue)), board(std::move(other_match.board)) {
}

void Match::addClientsNickNameToRepository(const int& client_id) {
    std::string nick_name;
    this->clients.at(client_id).getClientsNickName(nick_name);
    this->nick_names.saveNickNameRelatedToId(std::move(nick_name), client_id);
}

void Match::addClientWithIdToListOfClients(Socket&& client_socket, const int& client_id) {
    BlockingQueue<Instruction> new_listening_queue;
    listening_queues.insert(std::make_pair(client_id, std::move(new_listening_queue)));
    ClientHandler client(std::move(client_socket), this->listening_queues.at(client_id),
                         this->match_updates_queue, client_id, this->nick_names);
    clients.insert(std::make_pair(client_id, std::move(client)));
    this->accepted_clients++;
}

void Match::addSingleThreadedClientToMatchAndStart(Socket&& client_socket) {
    int client_id = this->accepted_clients;
    this->addClientWithIdToListOfClients(std::move(client_socket), client_id);
    this->addClientsNickNameToRepository(client_id);
    this->clients.at(client_id).startSingleThreadedClient(*this);
}

void Match::addClientToMatch(Socket&& client_socket, bool threaded_match) {
    int client_id = this->accepted_clients;
    this->addClientWithIdToListOfClients(std::move(client_socket), client_id);
    this->addClientsNickNameToRepository(client_id);
    this->clients.at(client_id).startThreadedClient(*this, threaded_match);
    LoadBoardInstruction instruction;
    match_updates_queue.push(std::make_shared<LoadBoardInstruction>(instruction));
}

void Match::stop() {
    std::cout << "detengo esta match" << std::endl;
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
        std::cout << "entro al catch" << std::endl;
        std::cout << clients.size() << std::endl;
        for (auto & client: clients) {
            // TODO hacer que si mueren matarlos.
            std::cout << "stopear cliente" << std::endl;
            client.second.stop();
            std::cout << "joineo" << std::endl;
            client.second.join();
            std::cout << "termine de joinear" << std::endl;
        }
    }
}

bool Match::hasActiveClients() const {
    return clients.size() > 0;
}

void Match::pushExitInstructionToUpdatesQueue() {
    std::shared_ptr<Instruction> exit_instruc =  std::make_shared<ExitInstruction>(MATCH_ID);
    this->match_updates_queue.push(exit_instruc);
}


/*
 *    std::vector<Position> positions;
    std::vector<char> characters;
    board.loadVectors(characters, positions);
    LoadBoardInstruction instr(std::move(characters), std::move(positions));
    instr.makeActionAndNotifyAllListeningQueues(listening_queues, clients, board);
 */
