#include "../../common/src/packet.h"
#include <unistd.h>
#include <arpa/inet.h>

#include <utility>
#include "../../common/src/unique_ptr.h"
#include "client_protocol.h"
#include "../../common/src/client_data.h"
#include "chessman_data.h"

#define ONE_BYTE 1
#define TWO_BYTES 2

std::map<uint16_t, std::vector<ClientData>>
ClientProtocol::receiveMatchesInfo(Socket &socket) {
  std::map<uint16_t, std::vector<ClientData>> matches_info;
  uint16_t matches_amount = getNumber16FromSocket(socket);
  for (uint16_t i = 0; i < matches_amount; i++) {
    uint16_t match_id = getNumber16FromSocket(socket);
    uint16_t clients_amount = getNumber16FromSocket(socket);
    std::vector<ClientData> client_data_vector;
    client_data_vector.reserve(clients_amount);
    for (uint16_t j = 0; j < clients_amount; j++) {
      uint16_t client_id = getNumber16FromSocket(socket);
      std::string client_name;
      getMessageFromSocket(socket, client_name);
      bool is_player = getNumber8FromSocket(socket);
      ClientData data(client_id, client_name, ClientData::ROLE_BLACK);
      uint16_t id = data.id;
      client_data_vector.push_back(std::move(data));
    }
    matches_info.insert(
            std::make_pair(match_id, std::move(client_data_vector)));
  }
  return matches_info;
}

void ClientProtocol::getAvailableRoles(Socket &socket,
                                       std::list<ClientData::Role> &roles) {
  uint8_t amount = getNumber8FromSocket(socket);
  for (uint8_t i = 0; i < amount; i++) {
    roles.push_back((ClientData::Role) getNumber8FromSocket(socket));
  }
}

void ClientProtocol::sendChosenGame(Socket &socket, uint16_t game_number) {
  Packet packet;
  this->changeNumberToBigEndianAndAddToPacket(packet, (uint16_t) game_number);
  socket.send(packet);
}

void
ClientProtocol::sendClientsNickName(Socket &socket, std::string &nick_name) {
  Packet packet;
  this->addStringAndItsLengthToPacket(packet, nick_name);
  socket.send(packet);
}

void ClientProtocol::sendChosenRole(Socket &socket, ClientData::Role role) {
  Packet packet;
  addNumber8ToPacket(packet, role);
  socket.send(packet);
}


void ClientProtocol::fillPacketWithChatMessage(Packet &packet,
                                               const std::string &message) {
  packet.addByte('c');
  addStringAndItsLengthToPacket(packet, message);
}

void
ClientProtocol::fillPacketWithMoveMessage(Packet &packet, Position &initial,
                                          Position &final) {
  packet.addByte('m');
  packet.addByte(initial.x());
  packet.addByte(initial.y());
  packet.addByte(final.x());
  packet.addByte(final.y());
}

void ClientProtocol::fillPacketWithPossibleMovesMessage(Packet &packet,
                                                        const Position &position) {
  packet.addByte('a');
  addNumber8ToPacket(packet, position.x());
  addNumber8ToPacket(packet, position.y());
}

void ClientProtocol::sendInstruction(Socket &socket,
                                     std::shared_ptr<RemoteClientInstruction> &instruction) {
  Packet packet;
  instruction->fillPacketWithInstructionsToSend(packet, *this);
  socket.send(packet);
}

void ClientProtocol::fillClientInstructionWithChat(Socket &socket,
                                                   std::shared_ptr<RemoteClientInstruction> &
                                                   ptr_instruction) {
  std::string nick_name;
  std::string message;
  this->getMessageFromSocket(socket, nick_name);
  this->getMessageFromSocket(socket, message);
  ptr_instruction = make_unique<RemoteClientChatInstruction>(nick_name,
                                                             message);

}

void ClientProtocol::fillClientInstructionWithExitMessage(Socket &socket,
                                                          std::shared_ptr<RemoteClientInstruction> &
                                                          ptr_instruction) {
  std::string nick_name;
  this->getMessageFromSocket(socket, nick_name);
  ptr_instruction = make_unique<RemoteClientExitMessageInstruction>(nick_name);
}

void ClientProtocol::fillClientInstructionWithLoadBoard(Socket &socket,
                                                        std::shared_ptr<RemoteClientInstruction> &
                                                        ptr_instruction) {
  uint8_t amount = getNumber8FromSocket(socket);
  std::vector<ChessmanData> chessman_data_vector;
  chessman_data_vector.reserve(amount);
  for (uint8_t i = 0; i < amount; i++) {
    char character_ = getCharFromSocket(socket);
    character_ = std::tolower(character_);
    char character[] = {character_, '\0'};
    bool white = getCharFromSocket(socket);
    std::string chessman(character);
    chessman += white ? "w" : "b";
    uint8_t x = getNumber8FromSocket(socket);
    uint8_t y = getNumber8FromSocket(socket);
    Position position(x, y);
    uint16_t prob_int = getNumber16FromSocket(socket);
    double prob = ((double) prob_int + 1) / (UINT16_MAX + 1);
    chessman_data_vector.push_back(ChessmanData(position, chessman, prob));
  }
  ptr_instruction = make_unique<RemoteClientLoadMessageInstruction>(
          std::move(chessman_data_vector));
}

void ClientProtocol::fillClientInstructionWithException(Socket &socket,
                                                        std::shared_ptr<RemoteClientInstruction> &ptr_instruction) {
  std::string message;
  this->getMessageFromSocket(socket, message);
  ptr_instruction = make_unique<RemoteClientExceptionInstruction>(message);
}

void ClientProtocol::fillClientInstructionWithPossibleMoves(Socket &socket,
                                                            std::shared_ptr<RemoteClientInstruction> &ptr_instruction) {
  uint8_t amount = getNumber8FromSocket(socket);
  std::list<Position> posible_moves;
  for (uint8_t i = 0; i < amount; i++) {
    uint8_t x = getNumber8FromSocket(socket);
    uint8_t y = getNumber8FromSocket(socket);
    Position position(x, y);
    posible_moves.push_back(position);
  }
  ptr_instruction = make_unique<RemoteClientPossibleMovesInstruction>(
          std::move(posible_moves));
}


void ClientProtocol::receiveInstruction(Socket &socket,
                                        std::shared_ptr<RemoteClientInstruction> &
                                        ptr_instruction) {
  Packet packet;
  socket.receive(packet, ONE_BYTE);
  char action = packet.getByte();
  switch (action) {
    case 'c':
      this->fillClientInstructionWithChat(socket, ptr_instruction);
      break;
    case 'l':
      this->fillClientInstructionWithLoadBoard(socket, ptr_instruction);
      break;
    case 'e':
      this->fillClientInstructionWithExitMessage(socket, ptr_instruction);
      break;
    case 'x':
      fillClientInstructionWithException(socket, ptr_instruction);
      break;
    case 'a':
      fillClientInstructionWithPossibleMoves(socket, ptr_instruction);
      break;
  }

}







