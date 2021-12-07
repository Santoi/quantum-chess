#include "clients_map.h"

ClientsMap::ClientsMap() : clients(), listening_queues(), mutex() {}

void
ClientsMap::addNewClient(Socket &&socket,
                         BlockingQueue<Instruction> &match_updates,
                         ClientData &client_data) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  BlockingQueue<Instruction> new_listening_queue;
  listening_queues.insert(
          std::make_pair(client_data.id, std::move(new_listening_queue)));
  ClientHandler client(std::move(socket),
                       listening_queues.at(client_data.id),
                       match_updates,
                       client_data);
  clients.insert(std::make_pair(client_data.id, std::move(client)));
}

void ClientsMap::startClient(uint16_t client_id) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  clients.at(client_id).start();
}

void ClientsMap::deleteClient(uint16_t client_id) {
  std::lock_guard<std::mutex> lock_guard(mutex);
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

void ClientsMap::pushInstrToClientListeningQueue(uint16_t client_id,
                                                 std::shared_ptr<Instruction> &instr_ptr) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  listening_queues.at(client_id).push(instr_ptr);
}

void
ClientsMap::addInstrToAllListeningQueues(
        std::shared_ptr<Instruction> &instr_ptr) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &listening_queue: listening_queues)
    listening_queue.second.push(instr_ptr);
}

size_t ClientsMap::size() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return clients.size();
}

void ClientsMap::stopAllClients() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  for (auto &client: clients) {
    client.second.stop();
    client.second.join();
  }
}

void
ClientsMap::getAvailableRoles(bool &white_available, bool &black_available) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  white_available = true;
  black_available = true;
  for (auto &client: clients) {
    ClientData::Role role = client.second.getData().role;
    if (role == ClientData::ROLE_WHITE)
      white_available = false;
    else if (role == ClientData::ROLE_BLACK)
      black_available = false;
    if (!white_available && !black_available)
      break;
  }
}

std::vector<ClientData> ClientsMap::getClientsData() const {
  std::vector<ClientData> output;
  output.reserve(clients.size());
  for (auto &client: clients)
    output.push_back(client.second.getData());
  return output;
}
