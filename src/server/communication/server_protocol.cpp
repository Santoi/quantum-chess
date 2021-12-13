#include "server_protocol.h"
#include "../../common/packet.h"
#include "instructions/instruction.h"
#include "instructions/chat_instruction.h"
#include "instructions/movement_instruction.h"
#include "match.h"
#include "../../common/client_data.h"
#include "instructions/possible_moves_instruction.h"
#include "instructions/possible_splits_instruction.h"
#include "instructions/split_instruction.h"
#include "instructions/possible_merges_instruction.h"
#include "instructions/same_chessman_instruction.h"
#include "instructions/entangled_chessman_instruction.h"
#include "instructions/merge_instruction.h"
#include "../../common/socket_closed.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm>
#include <map>
#include <string>
#include <list>
#include <vector>

#define POSSIBLE_MOVES_PREFIX 'a'

void ServerProtocol::sendMatchesInfo(Socket &socket,
                                     const std::map<uint16_t,
                                         std::vector<ClientData>>
                                     &matches_data) {
  Packet packet;
  changeNumberToBigEndianAndAddToPacket(packet, matches_data.size());
  for (auto &pair: matches_data) {
    changeNumberToBigEndianAndAddToPacket(packet, (uint16_t) pair.first);
    changeNumberToBigEndianAndAddToPacket(packet,
                                          (uint16_t) pair.second.size());
    for (auto &client_data: pair.second) {
      changeNumberToBigEndianAndAddToPacket(packet,
                                            (uint16_t) client_data.id);
      addStringAndItsLengthToPacket(packet, client_data.name);
      addNumber8ToPacket(packet, client_data.role);
    }
  }
  socket.send(packet);
}

void
ServerProtocol::sendAvailableRoles(Socket &socket,
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

ClientData::Role
ServerProtocol::receivePlayerRole(Socket &socket,
                                  const std::list<ClientData::Role> &roles) {
  auto role = (ClientData::Role) getNumber8FromSocket(socket);
  if (std::find(roles.begin(), roles.end(), role) != roles.end())
    return role;
  throw std::runtime_error("invalid role");
}

void ServerProtocol::getNickName(Socket &socket, std::string &nick_name) {
  this->getMessageFromSocket(socket, nick_name);
}

void ServerProtocol::fillChatInstruction(Socket &socket,
                                         const ClientData &client_data,
                                         std::shared_ptr<Instruction>
                                         &instruct_ptr) {
  std::string message;
  this->getMessageFromSocket(socket, message);
  instruct_ptr = std::make_shared<ChatInstruction>(client_data,
                                                   std::move(message));
}

void ServerProtocol::fillMovementInstruction(Socket &socket,
                                             const ClientData &client_data,
                                             std::shared_ptr<Instruction>
                                             &instruct_ptr) {
  uint8_t ix = getNumber8FromSocket(socket);
  uint8_t iy = getNumber8FromSocket(socket);
  uint8_t fx = getNumber8FromSocket(socket);
  uint8_t fy = getNumber8FromSocket(socket);
  Position initial(ix, iy);
  Position final(fx, fy);
  instruct_ptr = std::make_shared<MovementInstruction>(client_data, initial,
                                                       final);
}

void ServerProtocol::fillSplitInstruction(Socket &socket,
                                          const ClientData &client_data,
                                          std::shared_ptr<Instruction>
                                          &instruct_ptr) {
  uint8_t ix = getNumber8FromSocket(socket);
  uint8_t iy = getNumber8FromSocket(socket);
  uint8_t fx1 = getNumber8FromSocket(socket);
  uint8_t fy1 = getNumber8FromSocket(socket);
  uint8_t fx2 = getNumber8FromSocket(socket);
  uint8_t fy2 = getNumber8FromSocket(socket);
  Position initial(ix, iy);
  Position final1(fx1, fy1);
  Position final2(fx2, fy2);
  instruct_ptr = std::make_shared<SplitInstruction>(client_data, initial,
                                                    final1,
                                                    final2);
}

void ServerProtocol::fillMergeInstruction(Socket &socket,
                                          const ClientData &client_data,
                                          std::shared_ptr<Instruction>
                                          &instruct_ptr) {
  uint8_t i1x = getNumber8FromSocket(socket);
  uint8_t i1y = getNumber8FromSocket(socket);
  uint8_t i2x = getNumber8FromSocket(socket);
  uint8_t i2y = getNumber8FromSocket(socket);
  uint8_t fx = getNumber8FromSocket(socket);
  uint8_t fy = getNumber8FromSocket(socket);
  Position initial1(i1x, i1y);
  Position initial2(i2x, i2y);
  Position final(fx, fy);
  instruct_ptr = std::make_shared<MergeInstruction>(client_data, initial1,
                                                    initial2, final);
}

void ServerProtocol::fillPossibleMovesInstruction(Socket &socket,
                                                  const ClientData &client_data,
                                                  std::shared_ptr<Instruction>
                                                  &instruct_ptr) {
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
ServerProtocol::fillPossibleSplitsInstruction(Socket &socket,
                                              const ClientData &client_data,
                                              std::shared_ptr<Instruction>
                                              &instruct_ptr) {
  std::list<Position> positions;
  uint8_t x = getNumber8FromSocket(socket);
  uint8_t y = getNumber8FromSocket(socket);
  Position position(x, y);
  positions.push_back(position);
  instruct_ptr = std::make_shared<PossibleSplitsInstruction>(client_data,
                                                             std::move(
                                                                 positions));
}

void
ServerProtocol::fillPossibleMergesInstruction(Socket &socket,
                                              const ClientData &client_data,
                                              std::shared_ptr<Instruction>
                                              &instruct_ptr) {
  std::list<Position> positions;
  uint8_t amount = getNumber8FromSocket(socket);
  uint8_t x = getNumber8FromSocket(socket);
  uint8_t y = getNumber8FromSocket(socket);
  Position position(x, y);
  positions.push_back(position);
  if (amount == 2) {
    x = getNumber8FromSocket(socket);
    y = getNumber8FromSocket(socket);
    position = Position(x, y);
    positions.push_back(position);
  }
  instruct_ptr = std::make_shared<PossibleMergesInstruction>(client_data,
                                                             std::move(
                                                                 positions));
}

void ServerProtocol::fillSameChessmanInstruction(Socket &socket,
                                                 const ClientData &client_data,
                                                 std::shared_ptr<Instruction>
                                                 &instruct_ptr) {
  std::list<Position> positions;
  uint8_t x = getNumber8FromSocket(socket);
  uint8_t y = getNumber8FromSocket(socket);
  Position position(x, y);
  positions.push_back(position);
  instruct_ptr = std::make_shared<SameChessmanInstruction>(client_data,
                                                           std::move(
                                                               positions));
}

void
ServerProtocol::fillEntangledChessmenInstruction(Socket &socket,
                                                 const ClientData &client_data,
                                                 std::shared_ptr<Instruction>
                                                 &instruct_ptr) {
  std::list<Position> positions;
  uint8_t x = getNumber8FromSocket(socket);
  uint8_t y = getNumber8FromSocket(socket);
  Position position(x, y);
  positions.push_back(position);
  instruct_ptr = std::make_shared<EntangledChessmanInstruction>(client_data,
                                                                std::move(
                                                                    positions));
}


void
ServerProtocol::receiveAndFillInstruction(Socket &socket,
                                          const ClientData &client_data,
                                          std::shared_ptr<Instruction>
                                          &instruct_ptr) {
  Packet packet;
  socket.receive(packet, 1);
  if (packet.size() != 1)
    throw SocketClosed();
  char action = packet.getByte();

  switch (action) {
    case CHAT_PREFIX:
      fillChatInstruction(socket, client_data, instruct_ptr);
      break;
    case MOVE_PREFIX:
      fillMovementInstruction(socket, client_data, instruct_ptr);
      break;
    case POSSIBLE_MOVES_PREFIX:
      fillPossibleMovesInstruction(socket, client_data, instruct_ptr);
      break;
    case POSSIBLE_SPLITS_PREFIX:
      fillPossibleSplitsInstruction(socket, client_data, instruct_ptr);
      break;
    case POSSIBLE_MERGES_PREFIX:
      fillPossibleMergesInstruction(socket, client_data, instruct_ptr);
      break;
    case SPLIT_PREFIX:
      fillSplitInstruction(socket, client_data, instruct_ptr);
      break;
    case SAME_CHESSMAN_PREFIX:
      fillSameChessmanInstruction(socket, client_data, instruct_ptr);
      break;
    case ENTANGLED_CHESSMEN_PREFIX:
      fillEntangledChessmenInstruction(socket, client_data, instruct_ptr);
      break;
    case MERGE_PREFIX:
      fillMergeInstruction(socket, client_data, instruct_ptr);
      break;
    default:
      throw std::runtime_error("invalid message received");
  }
}

void ServerProtocol::fillPacketWithChatMessage(Packet &packet,
                                               const ClientData &client_data,
                                               const std::string &message,
                                               const std::string &timestamp) {
  packet.addByte(CHAT_PREFIX);
  changeNumberToBigEndianAndAddToPacket(packet, client_data.id);
  addStringAndItsLengthToPacket(packet, client_data.name);
  addStringAndItsLengthToPacket(packet, timestamp);
  addStringAndItsLengthToPacket(packet, message);
}

void
ServerProtocol::fillPacketWithExceptionMessage(Packet &packet,
                                               const std::string &message) {
  packet.addByte(EXCEPTION_PREFIX);
  this->addStringAndItsLengthToPacket(packet, message);
}

void ServerProtocol::fillPacketWithLoadBoardMessage(Packet &packet,
                                                    const std::vector<
                                                        SquareData> &data,
                                                    bool white) {
  packet.addByte(LOAD_BOARD_PREFIX);
  packet.addByte(data.size());
  for (auto &square: data) {
    packet.addByte(square.chessman);
    packet.addByte(square.white);
    packet.addByte(square.position.x());
    packet.addByte(square.position.y());
    uint16_t prob_int = square.probability * (UINT16_MAX + 1) - 1;
    changeNumberToBigEndianAndAddToPacket(packet, prob_int);
  }
  addNumber8ToPacket(packet, white);
}

void ServerProtocol::fillPacketWithPossibleMoves(Packet &packet,
                                                 const std::list<Position>
                                                 &positions) {
  packet.addByte(POSSIBLE_MOVES_PREFIX);
  addNumber8ToPacket(packet, positions.size());
  for (auto &position: positions) {
    addNumber8ToPacket(packet, position.x());
    addNumber8ToPacket(packet, position.y());
  }
}

void ServerProtocol::fillPacketWithPossibleSplits(Packet &packet,
                                                  const std::list<Position>
                                                  &positions) {
  packet.addByte(POSSIBLE_SPLITS_PREFIX);
  addNumber8ToPacket(packet, positions.size());
  for (auto &position: positions) {
    addNumber8ToPacket(packet, position.x());
    addNumber8ToPacket(packet, position.y());
  }
}

void ServerProtocol::fillPacketWithPossibleMerges(Packet &packet,
                                                  const std::list<Position>
                                                  &positions) {
  packet.addByte(POSSIBLE_MERGES_PREFIX);
  addNumber8ToPacket(packet, positions.size());
  for (auto &position: positions) {
    addNumber8ToPacket(packet, position.x());
    addNumber8ToPacket(packet, position.y());
  }
}

void
ServerProtocol::fillPacketWithSameChessmanInstruction(Packet &packet,
                                                      const std::list<Position>
                                                      &positions) {
  packet.addByte(SAME_CHESSMAN_PREFIX);
  addNumber8ToPacket(packet, positions.size());
  for (auto &position: positions) {
    addNumber8ToPacket(packet, position.x());
    addNumber8ToPacket(packet, position.y());
  }
}

void ServerProtocol::
fillPacketWithEntangledChessmanInstruction(Packet &packet,
                                           const std::list<Position>
                                           &positions) {
  packet.addByte(ENTANGLED_CHESSMEN_PREFIX);
  addNumber8ToPacket(packet, positions.size());
  for (auto &position: positions) {
    addNumber8ToPacket(packet, position.x());
    addNumber8ToPacket(packet, position.y());
  }
}

void ServerProtocol::fillPacketLogMessage(Packet &packet,
                                          std::list<std::string> &log) {
  packet.addByte(LOG_PREFIX);
  changeNumberToBigEndianAndAddToPacket(packet, log.size());
  for (auto &entry: log) {
    addStringAndItsLengthToPacket(packet, entry);
  }
}

void ServerProtocol::sendPacket(Socket &socket,
                                std::shared_ptr<Instruction> &instruct_ptr,
                                const ClientData &client_data) {
  Packet packet;
  instruct_ptr->fillPacketWithInstructionToSend(*this, packet, client_data);
  socket.send(packet);
}

void ServerProtocol::fillPacketWithExitMessage(Packet &packet,
                                               const std::string &nick_name) {
  packet.addByte(EXIT_PREFIX);
  this->addStringAndItsLengthToPacket(packet, nick_name);
}

void ServerProtocol::fillPacketWithSoundMessage(Packet &packet, uint8_t sound) {
  packet.addByte(SOUND_PREFIX);
  addNumber8ToPacket(packet, sound);
}










