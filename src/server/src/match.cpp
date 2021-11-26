#include "match.h"
#include "client_handler.h"
#include "quantum_chess/board.h"
#include "instructions/instruction.h"
#include "instructions/exit_instruction.h"
#include "instructions/load_board_instruction.h"

#define MATCH_ID -1

// TODO AVeriguar donde arranca match.

Match::Match()
        : Thread(), board(), clients(), listening_queues(),
          match_updates_queue() {
}

Match::Match(Match &&other_match) : Thread(std::move(other_match)),
                                    board(std::move(other_match.board)),
                                    clients(std::move(other_match.clients)),
                                    listening_queues(std::move(
                                            other_match.listening_queues)),
                                    match_updates_queue(std::move(
                                            other_match.match_updates_queue)) {}

ClientData Match::askClientData(Socket &socket, uint16_t client_id) {
  ServerProtocol protocol;
  std::string nickname;
  protocol.getNickName(socket, nickname);
  std::list<ClientData::Role> available_roles = getAvailableRoles();
  protocol.sendAvailableRoles(socket, available_roles);
  ClientData::Role role = protocol.receivePlayerRole(socket,
                                                     available_roles);
  ClientData client_data(client_id, nickname, role);
  return client_data;
}

void Match::addClientWithIdToListOfClients(Socket &&client_socket,
                                           ClientData &client_data) {
  BlockingQueue<Instruction> new_listening_queue;
  uint16_t client_id = client_data.id;
  listening_queues.insert(
          std::make_pair(client_id, std::move(new_listening_queue)));
  ClientHandler client(std::move(client_socket),
                       this->listening_queues.at(client_id),
                       this->match_updates_queue,
                       client_data);
  clients.insert(std::make_pair(client_id, std::move(client)));
}

void Match::addClientToMatch(Socket &&client_socket, uint16_t client_id) {
  ClientData client_data = askClientData(client_socket, client_id);
  this->addClientWithIdToListOfClients(std::move(client_socket), client_data);
  this->clients.at(client_id).start();
  LoadBoardInstruction instruction;
  match_updates_queue.push(std::make_shared<LoadBoardInstruction>(instruction));
}

void Match::deleteClientWithId(uint16_t client_id) {
  auto it_queue = listening_queues.begin();
  auto it_client = clients.begin();
  for (; it_queue != listening_queues.end() && it_client != clients.end();
         ++it_queue, ++it_client) {
    if (it_queue->first == client_id) {
      it_client->second.stop();
      it_client->second.join();
      clients.erase(it_client);
      listening_queues.erase(it_queue);
      break;
    }
  }
}

void Match::stop() {
  match_updates_queue.close();
}

void Match::checkAndNotifyUpdates() {
  std::shared_ptr<Instruction> instruc_ptr;
  this->match_updates_queue.pop(instruc_ptr);
  instruc_ptr->makeActionAndNotifyAllListeningQueues(this->listening_queues,
                                                     *this,
                                                     match_updates_queue);
}

void Match::run() {
  board.load();
  try {
    while (true)
      checkAndNotifyUpdates();
  }
  catch (const BlockingQueueClosed &error) {
    for (auto &client: clients) {
      client.second.stop();
      client.second.join();
    }
  }

}

bool Match::hasActiveClients() const {
  return !clients.empty();
}

std::list<ClientData::Role> Match::getAvailableRoles() {
  std::list<ClientData::Role> available_roles;
  bool white_available = true, black_available = true;
  for (auto &client: clients) {
    ClientData::Role role = client.second.getData().role;
    if (role == ClientData::ROLE_WHITE)
      white_available = false;
    else if (role == ClientData::ROLE_BLACK)
      black_available = false;
    if (!white_available && !black_available)
      break;
  }
  if (white_available)
    available_roles.push_back(ClientData::ROLE_WHITE);
  if (black_available)
    available_roles.push_back(ClientData::ROLE_BLACK);
  available_roles.push_back(ClientData::ROLE_SPECTATOR);
  return available_roles;
}

std::vector<const ClientData *> Match::getClientsData() const {
  std::vector<const ClientData *> output;
  output.reserve(clients.size());
  for (auto &client: clients)
    output.push_back(&(client.second.getData()));
  return output;
}

Board &Match::getBoard() {
  return board;
}
