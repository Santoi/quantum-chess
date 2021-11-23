#include "server_protocol.h"
#include "../../common/src/packet.h"
#include "instructions/instruction.h"
#include "instructions/chat_instruction.h"
#include "instructions/movement_instruction.h"
#include "match.h"
#include "../../common/src/client_data.h"
#include "instructions/possible_moves_instruction.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm>

#define ONE_BYTE 1
#define TWO_BYTES 2


void ServerProtocol::sendMatchesInfo(Socket &socket,
                                     const std::map<uint16_t, std::unique_ptr<Match>> &matches) {
  Packet packet;
  changeNumberToBigEndianAndAddToPacket(packet, matches.size());
  for (auto &pair: matches) {
    changeNumberToBigEndianAndAddToPacket(packet, (uint16_t) pair.first);
    std::vector<const ClientData *> client_data_repository =
            pair.second->getClientsData();
    changeNumberToBigEndianAndAddToPacket(packet,
                                          (uint16_t) client_data_repository.size());
    for (auto &client_data: client_data_repository) {
      changeNumberToBigEndianAndAddToPacket(packet,
                                            (uint16_t) client_data->id);
      addStringAndItsLengthToPacket(packet, client_data->name);
      addNumber8ToPacket(packet, client_data->role);
    }
  }
  socket.send(packet);
}

void ServerProtocol::sendAvailableRoles(Socket &socket,
                                        const std::list<ClientData::Role> &roles) {
  Packet packet;
  addNumber8ToPacket(packet, roles.size());
  for (auto &role: roles)
    addNumber8ToPacket(packet, role);
  socket.send(packet);
}

uint16_t ServerProtocol::receiveChosenGame(Socket &socket) {
  return (uint16_t) (this->getNumber16FromSocket(socket));
}

ClientData::Role ServerProtocol::receivePlayerRole(Socket &socket,
                                                   const std::list<ClientData::Role> &roles) {
  auto role = (ClientData::Role) getNumber8FromSocket(socket);
  if (std::find(roles.begin(), roles.end(), role) != roles.end())
    return role;
  throw std::runtime_error("invalid role");
}

void ServerProtocol::getNickName(Socket &socket, std::string &nick_name) {
  this->getMessageFromSocket(socket, nick_name);
}

void ServerProtocol::fillChatInstructions(Socket &socket,
                                          const ClientData &client_data,
                                          std::shared_ptr<Instruction> &instruct_ptr) {
  std::string message;
  this->getMessageFromSocket(socket, message);
  instruct_ptr = std::make_shared<ChatInstruction>(client_data,
                                                   std::move(message));
}

void ServerProtocol::fillMovementInstructions(Socket &socket,
                                              const ClientData &client_data,
                                              std::shared_ptr<Instruction> &instruct_ptr) {
  uint8_t ix = getNumber8FromSocket(socket);
  uint8_t iy = getNumber8FromSocket(socket);
  uint8_t fx = getNumber8FromSocket(socket);
  uint8_t fy = getNumber8FromSocket(socket);
  Position initial(ix, iy);
  Position final(fx, fy);
  instruct_ptr = std::make_shared<MovementInstruction>(client_data, initial,
                                                       final);
}

void ServerProtocol::fillPossibleMovesInstruction(Socket &socket,
                                                  const ClientData &client_data,
                                                  std::shared_ptr<Instruction> &instruct_ptr) {
  std::list<Position> positions;
  uint8_t x = getNumber8FromSocket(socket);
  uint8_t y = getNumber8FromSocket(socket);
  Position position(x, y);
  positions.push_back(position);
  instruct_ptr = std::make_shared<PossibleMovesInstruction>(client_data,
                                                            std::move(
                                                                    positions));
}


void
ServerProtocol::fillInstructions(Socket &socket, const ClientData &client_data,
                                 std::shared_ptr<Instruction> &instruct_ptr) {
  Packet packet;
  socket.receive(packet, ONE_BYTE);
  char action = packet.getByte();

  switch (action) {
    case 'c':
      fillChatInstructions(socket, client_data, instruct_ptr);
      break;
    case 'm':
      fillMovementInstructions(socket, client_data, instruct_ptr);
      break;
    case 'a':
      fillPossibleMovesInstruction(socket, client_data, instruct_ptr);
  }
}

void ServerProtocol::fillPacketWithChatInfo(Packet &packet,
                                            const std::string &nick_name,
                                            const std::string &message) {
  packet.addByte('c');
  this->addStringAndItsLengthToPacket(packet, nick_name);
  this->addStringAndItsLengthToPacket(packet, message);
}

void ServerProtocol::fillPacketWithExceptionInfo(Packet &packet,
                                                 const std::string &message) {
  packet.addByte('x');
  this->addStringAndItsLengthToPacket(packet, message);
}

void ServerProtocol::fillPacketWithLoadBoardInfo(Packet &packet,
                                                 const std::vector<char> &characters,
                                                 const std::vector<bool> &colors,
                                                 const std::vector<Position> &positions,
                                                 const std::vector<double> &probabilities) {
  packet.addByte('l');
  packet.addByte(characters.size());
  for (uint16_t i = 0; i < characters.size(); i++) {
    packet.addByte(characters[i]);
    packet.addByte(colors[i]);
    packet.addByte(positions[i].x());
    packet.addByte(positions[i].y());
    uint16_t prob_int = probabilities[i] * (UINT16_MAX + 1) - 1;
    changeNumberToBigEndianAndAddToPacket(packet, prob_int);
  }
}

void ServerProtocol::fillPacketWithPossibleMoves(Packet &packet,
                                                 const std::list<Position> &positions) {
  packet.addByte('a');
  addNumber8ToPacket(packet, positions.size());
  for (auto &position: positions) {
    addNumber8ToPacket(packet, position.x());
    addNumber8ToPacket(packet, position.y());
  }
}

void ServerProtocol::sendPacketWithUpdates(Socket &socket,
                                           std::shared_ptr<Instruction> &instruct_ptr,
                                           const ClientData &client_data) {
  Packet packet;
  instruct_ptr->fillPacketWithInstructionsToSend(*this, packet, client_data);
  socket.send(packet);
}

void ServerProtocol::fillPacketWithExitInfo(Packet &packet,
                                            const std::string &nick_name) {
  packet.addByte('e');
  this->addStringAndItsLengthToPacket(packet, nick_name);
}








