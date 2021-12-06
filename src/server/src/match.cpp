#include "match.h"

#include <utility>
#include "client_handler.h"
#include "quantum_chess/board.h"
#include "instructions/instruction.h"
#include "instructions/exit_instruction.h"
#include "instructions/load_board_instruction.h"
#include "instructions/chat_instruction.h"
#include "../../common/src/socket.h"

// TODO maps de listening queues y client hanlders hay que hacerlos protegidos,
//  podria haber race condition si el cliente manda algo y justo se une alguien.

Match::Match(std::ifstream &file_)
        : Thread(), board(), clients_map(), match_updates_queue(),
          file(file_) {}

Match::Match(Match &&other) : Thread(std::move(other)),
                              board(std::move(other.board)), clients_map(),
                              match_updates_queue(
                                      std::move(other.match_updates_queue)),
                              file(other.file) {}

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

void Match::addClientToMatch(Socket &&client_socket, uint16_t client_id) {
  ClientData client_data = askClientData(client_socket, client_id);
  clients_map.addNewClient(std::move(client_socket), match_updates_queue,
                           client_data);
  clients_map.startClient(client_id);
  std::shared_ptr<Instruction> chat_instruction = std::make_shared<ChatInstruction>(
          client_data, "has joined");
  match_updates_queue.push(chat_instruction);
  LoadBoardInstruction instruction;
  match_updates_queue.push(std::make_shared<LoadBoardInstruction>(instruction));
}

void Match::deleteClientWithId(uint16_t client_id) {
  clients_map.deleteClient(client_id);
}

void Match::stop() {
  match_updates_queue.close();
}

void Match::addInstrToClientListeningQueue(uint16_t client_id,
                                           std::shared_ptr<Instruction> &instr_ptr) {
  clients_map.addInstrToClientListeningQueue(client_id, instr_ptr);
}

void
Match::addInstrToAllListeningQueues(std::shared_ptr<Instruction> instr_ptr) {
  clients_map.addInstrToAllListeningQueues(instr_ptr);
}

void
Match::addInstrToUpdateQueue(std::shared_ptr<Instruction> instr_ptr) {
  match_updates_queue.push(std::move(instr_ptr));
}


void Match::checkAndNotifyUpdates() {
  auto instruct_ptr = match_updates_queue.pop();
  instruct_ptr->makeActionAndNotify(
          *this);
}

void Match::run() {
  board.load(file);
  try {
    while (true)
      checkAndNotifyUpdates();
  }
  catch (const BlockingQueueClosed &error) {
    clients_map.stopAllClients();
  }
}

void Match::runCatchingExceptions() {
  try {
    run();
  }
  catch (const std::exception &e) {
    clients_map.stopAllClients();
    std::cerr << "Error:" << e.what() << std::endl;
  }
  catch (...) {
    clients_map.stopAllClients();
    std::cerr << "Unknown error" << std::endl;
  }
}

bool Match::hasActiveClients() {
  return clients_map.size() > 0;
}

std::list<ClientData::Role> Match::getAvailableRoles() {
  std::list<ClientData::Role> available_roles;
  bool white_available, black_available;
  clients_map.getAvailableRoles(white_available, black_available);
  if (white_available)
    available_roles.push_back(ClientData::ROLE_WHITE);
  if (black_available)
    available_roles.push_back(ClientData::ROLE_BLACK);
  available_roles.push_back(ClientData::ROLE_SPECTATOR);
  return available_roles;
}

// TODO Pasar referencia?
std::vector<ClientData> Match::getClientsData() const {
  return clients_map.getClientsData();
}

Board &Match::getBoard() {
  return board;
}
