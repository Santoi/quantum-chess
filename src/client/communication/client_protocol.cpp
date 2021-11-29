#include "../../common/src/packet.h"
#include <unistd.h>
#include <arpa/inet.h>

#include <utility>
#include "../../common/src/unique_ptr.h"
#include "client_protocol.h"
#include "../../common/src/client_data.h"
#include "chessman_data.h"
#include "../../common/src/socket_closed.h"

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
      auto role = (ClientData::Role) getNumber8FromSocket(socket);
      ClientData data(client_id, client_name, role);
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
  packet.addByte(CHAT_PREFIX);
  addStringAndItsLengthToPacket(packet, message);
}

void
ClientProtocol::fillPacketWithMoveMessage(Packet &packet, Position &initial,
                                          Position &final) {
  packet.addByte(MOVE_PREFIX);
  packet.addByte(initial.x());
  packet.addByte(initial.y());
  packet.addByte(final.x());
  packet.addByte(final.y());
}

void
ClientProtocol::fillPacketWithSplitMessage(Packet &packet, Position &from,
                                           Position &to1, Position &to2) {
  packet.addByte(SPLIT_PREFIX);
  packet.addByte(from.x());
  packet.addByte(from.y());
  packet.addByte(to1.x());
  packet.addByte(to1.y());
  packet.addByte(to2.x());
  packet.addByte(to2.y());
}

void ClientProtocol::fillPacketWithMergeMessage(Packet &packet,
                                                const Position &from1,
                                                const Position &from2,
                                                const Position &to) {
  packet.addByte(MERGE_PREFIX);
  packet.addByte(from1.x());
  packet.addByte(from1.y());
  packet.addByte(from2.x());
  packet.addByte(from2.y());
  packet.addByte(to.x());
  packet.addByte(to.y());
}

void ClientProtocol::fillPacketWithPossibleMovesMessage(Packet &packet,
                                                        const Position &position) {
  packet.addByte(POSSIBLE_MOVES_PREFIX);
  addNumber8ToPacket(packet, position.x());
  addNumber8ToPacket(packet, position.y());
}

void ClientProtocol::fillPacketWithPossibleSplitsMessage(Packet &packet,
                                                         const Position &position) {
  packet.addByte(POSSIBLE_SPLITS_PREFIX);
  addNumber8ToPacket(packet, position.x());
  addNumber8ToPacket(packet, position.y());
}

void ClientProtocol::fillPacketWithPossibleMergesMessage(Packet &packet,
                                                         const Position &position) {
  packet.addByte(POSSIBLE_MERGES_PREFIX);
  addNumber8ToPacket(packet, 1);
  addNumber8ToPacket(packet, position.x());
  addNumber8ToPacket(packet, position.y());
}

void ClientProtocol::fillPacketWithPossibleMergesMessage(Packet &packet,
                                                         const Position &position1,
                                                         const Position &position2) {
  packet.addByte(POSSIBLE_MERGES_PREFIX);
  addNumber8ToPacket(packet, 2);
  addNumber8ToPacket(packet, position1.x());
  addNumber8ToPacket(packet, position1.y());
  addNumber8ToPacket(packet, position2.x());
  addNumber8ToPacket(packet, position2.y());
}

void ClientProtocol::fillPacketWithSameChessmanInstruction(Packet &packet,
                                                           Position &position) {
  packet.addByte(SAME_CHESSMAN_PREFIX);
  addNumber8ToPacket(packet, position.x());
  addNumber8ToPacket(packet, position.y());
}

void ClientProtocol::fillPacketWithEntangledChessmanInstruction(Packet &packet,
                                                                Position &position) {
  packet.addByte(ENTANGLED_CHESSMEN_PREFIX);
  addNumber8ToPacket(packet, position.x());
  addNumber8ToPacket(packet, position.y());
}


void ClientProtocol::sendInstruction(Socket &socket,
                                     std::shared_ptr<RemoteClientInstruction> &instruction) {
  Packet packet;
  instruction->fillPacketWithInstructionsToSend(packet, *this);
  socket.send(packet);
}

void ClientProtocol::fillChatInstruction(Socket &socket,
                                         std::shared_ptr<RemoteClientInstruction> &
                                         ptr_instruction) {
  std::string nick_name;
  std::string message;
  this->getMessageFromSocket(socket, nick_name);
  this->getMessageFromSocket(socket, message);
  ptr_instruction = make_unique<RemoteClientChatInstruction>(nick_name,
                                                             message);

}

void ClientProtocol::fillExitInstruction(Socket &socket,
                                         std::shared_ptr<RemoteClientInstruction> &
                                         ptr_instruction) {
  std::string nick_name;
  this->getMessageFromSocket(socket, nick_name);
  ptr_instruction = make_unique<RemoteClientExitMessageInstruction>(nick_name);
}

void ClientProtocol::fillLoadBoardInstruction(Socket &socket,
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
  ptr_instruction = make_unique<RemoteClientLoadBoardInstruction>(
          std::move(chessman_data_vector));
}

void ClientProtocol::fillShortLogInstruction(Socket &socket,
                                             std::shared_ptr<RemoteClientInstruction> &ptr_instruction) {
  std::string message;
  this->getMessageFromSocket(socket, message);
  ptr_instruction = make_unique<RemoteClientExceptionInstruction>(message);
}

void ClientProtocol::fillPossibleMovesInstruction(Socket &socket,
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

void ClientProtocol::fillPossibleSplitsInstruction(Socket &socket,
                                                   std::shared_ptr<RemoteClientInstruction> &ptr_instruction) {
  uint8_t amount = getNumber8FromSocket(socket);
  std::list<Position> posible_moves;
  for (uint8_t i = 0; i < amount; i++) {
    uint8_t x = getNumber8FromSocket(socket);
    uint8_t y = getNumber8FromSocket(socket);
    Position position(x, y);
    posible_moves.push_back(position);
  }
  ptr_instruction = make_unique<RemoteClientPossibleSplitsInstruction>(
          std::move(posible_moves));
}

void ClientProtocol::fillPossibleMergesInstruction(Socket &socket,
                                                   std::shared_ptr<RemoteClientInstruction> &ptr_instruction) {
  uint8_t amount = getNumber8FromSocket(socket);
  std::list<Position> posible_moves;
  for (uint8_t i = 0; i < amount; i++) {
    uint8_t x = getNumber8FromSocket(socket);
    uint8_t y = getNumber8FromSocket(socket);
    Position position(x, y);
    posible_moves.push_back(position);
  }
  ptr_instruction = make_unique<RemoteClientPossibleMergesInstruction>(
          std::move(posible_moves));
}

void ClientProtocol::fillSameChessmanInstruction(Socket &socket,
                                                 std::shared_ptr<RemoteClientInstruction> &ptr_instruction) {
  uint8_t amount = getNumber8FromSocket(socket);
  std::list<Position> posible_moves;
  for (uint8_t i = 0; i < amount; i++) {
    uint8_t x = getNumber8FromSocket(socket);
    uint8_t y = getNumber8FromSocket(socket);
    Position position(x, y);
    posible_moves.push_back(position);
  }
  ptr_instruction = make_unique<RemoteClientSameChessmanInstruction>(
          std::move(posible_moves));
}

void ClientProtocol::fillEntangledChessmanInstruction(Socket &socket,
                                                      std::shared_ptr<RemoteClientInstruction> &ptr_instruction) {
  uint8_t amount = getNumber8FromSocket(socket);
  std::list<Position> posible_moves;
  for (uint8_t i = 0; i < amount; i++) {
    uint8_t x = getNumber8FromSocket(socket);
    uint8_t y = getNumber8FromSocket(socket);
    Position position(x, y);
    posible_moves.push_back(position);
  }
  ptr_instruction = make_unique<RemoteClientEntangledChessmanInstruction>(
          std::move(posible_moves));
}

void ClientProtocol::fillSoundInstruction(Socket &socket,
                                          std::shared_ptr<RemoteClientInstruction> &ptr_instruction) {
  uint8_t sound = getNumber8FromSocket(socket);
  ptr_instruction = std::make_shared<RemoteClientSoundInstruction>(sound);
}

void ClientProtocol::receiveInstruction(Socket &socket,
                                        std::shared_ptr<RemoteClientInstruction> &
                                        ptr_instruction) {
  Packet packet;
  socket.receive(packet, 1);
  if (packet.size() != 1)
    throw SocketClosed();
  char action = packet.getByte();
  switch (action) {
    case CHAT_PREFIX:
      fillChatInstruction(socket, ptr_instruction);
      break;
    case LOAD_BOARD_PREFIX:
      fillLoadBoardInstruction(socket, ptr_instruction);
      break;
    case EXIT_PREFIX:
      fillExitInstruction(socket, ptr_instruction);
      break;
    case SHORT_LOG_PREFIX:
      fillShortLogInstruction(socket, ptr_instruction);
      break;
    case POSSIBLE_MOVES_PREFIX:
      fillPossibleMovesInstruction(socket, ptr_instruction);
      break;
    case POSSIBLE_SPLITS_PREFIX:
      fillPossibleSplitsInstruction(socket, ptr_instruction);
      break;
    case POSSIBLE_MERGES_PREFIX:
      fillPossibleMergesInstruction(socket, ptr_instruction);
      break;
    case SAME_CHESSMAN_PREFIX:
      fillSameChessmanInstruction(socket, ptr_instruction);
      break;
    case ENTANGLED_CHESSMEN_PREFIX:
      fillEntangledChessmanInstruction(socket, ptr_instruction);
      break;
    case SOUND_PREFIX:
      fillSoundInstruction(socket, ptr_instruction);
      break;
  }

}










