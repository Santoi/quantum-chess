#include "remote_client_instructions.h"
#include "client_protocol.h"
#include "../position.h"
#include "../game/game.h"
#include <iostream>
#include <utility>

void RemoteClientInstruction::fillPacketWithInstructionsToSend(Packet &packet,
                                                               ClientProtocol &protocol) {

}

RemoteClientChatInstruction::RemoteClientChatInstruction(std::string message_) :
        client_id(0), nickname(), message(message_), timestamp() {}


RemoteClientChatInstruction::RemoteClientChatInstruction(uint16_t client_id,
                                                         std::string nick_name,
                                                         std::string message,
                                                         std::string timestamp)
        : client_id(client_id), nickname(std::move(nick_name)),
          message(std::move(message)),
          timestamp(std::move(timestamp)) {
}

void RemoteClientChatInstruction::makeAction(Game &game) {
  std::cout << nickname << " envia: " << this->message
            << std::endl;
}

void
RemoteClientChatInstruction::fillPacketWithInstructionsToSend(Packet &packet,
                                                              ClientProtocol &protocol) {
  protocol.fillPacketWithChatMessage(packet, message);
}

// TODO hacer como los del chat
RemoteClientExitMessageInstruction::RemoteClientExitMessageInstruction(
        const std::string &nick_name)
        : nickname(nick_name) {
}

void RemoteClientExitMessageInstruction::makeAction(Game &game) {
  std::cout << nickname << " se fue de la partida."
            << std::endl;
}

RemoteClientLoadBoardInstruction::RemoteClientLoadBoardInstruction(
        std::vector<ChessmanData> &&chessman_data_vector_) :
        chessman_data_vector(std::move(chessman_data_vector_)) {}

void RemoteClientLoadBoardInstruction::makeAction(Game &game) {
  game.load(chessman_data_vector);
}

RemoteClientMoveInstruction::RemoteClientMoveInstruction(
        const Position &initial_,
        const Position &final_) : initial(initial_), final(final_) {}

void RemoteClientMoveInstruction::makeAction(Game &game) {}

void
RemoteClientMoveInstruction::fillPacketWithInstructionsToSend(Packet &packet,
                                                              ClientProtocol &protocol) {
  protocol.fillPacketWithMoveMessage(packet, initial, final);
}

RemoteClientExceptionInstruction::RemoteClientExceptionInstruction(
        const std::string &message)
        : message(message) {}

void RemoteClientExceptionInstruction::makeAction(Game &game) {
  std::cout << "Error: " << this->message << std::endl;
}

void RemoteClientExceptionInstruction::fillPacketWithInstructionsToSend(
        Packet &packet, ClientProtocol &protocol) {
}

RemoteClientPossibleMovesInstruction::RemoteClientPossibleMovesInstruction
        (std::list<Position> &&positions_) :
        positions(std::move(positions_)) {}

void RemoteClientPossibleMovesInstruction::makeAction(Game &game) {
  game.moveTiles(positions);
}

void
RemoteClientPossibleMovesInstruction::fillPacketWithInstructionsToSend(
        Packet &packet,
        ClientProtocol &protocol) {
  protocol.fillPacketWithPossibleMovesMessage(packet, *positions.begin());
}

RemoteClientPossibleSplitsInstruction::RemoteClientPossibleSplitsInstruction
        (std::list<Position> &&positions_) :
        positions(std::move(positions_)) {}

void RemoteClientPossibleSplitsInstruction::makeAction(Game &game) {
  game.splitTiles(positions);
}

void
RemoteClientPossibleSplitsInstruction::fillPacketWithInstructionsToSend(
        Packet &packet,
        ClientProtocol &protocol) {
  protocol.fillPacketWithPossibleSplitsMessage(packet, *positions.begin());
}

RemoteClientPossibleMergesInstruction::RemoteClientPossibleMergesInstruction
        (std::list<Position>
         &&positions_) :
        positions(std::move(positions_)) {}

void RemoteClientPossibleMergesInstruction::makeAction(Game &game) {
  game.mergeTiles(positions);
}

void
RemoteClientPossibleMergesInstruction::fillPacketWithInstructionsToSend(
        Packet &packet,
        ClientProtocol &protocol) {
  if (positions.size() == 1)
    protocol.fillPacketWithPossibleMergesMessage(packet, *positions.begin());
  else if (positions.size() == 2)
    protocol.fillPacketWithPossibleMergesMessage(packet, *positions.begin(),
                                                 *(++positions.begin()));
}


RemoteClientSplitInstruction::RemoteClientSplitInstruction(
        const Position &from_, const Position &to1_, const Position &to2_)
        : from(from_), to1(to1_), to2(to2_) {}

void RemoteClientSplitInstruction::makeAction(Game &game) {}

void
RemoteClientSplitInstruction::fillPacketWithInstructionsToSend(Packet &packet,
                                                               ClientProtocol &protocol) {
  protocol.fillPacketWithSplitMessage(packet, from, to1, to2);
}

RemoteClientMergeInstruction::RemoteClientMergeInstruction(
        const Position &from1_, const Position &from2_, const Position &to_)
        : from1(from1_), from2(from2_), to(to_) {}

void RemoteClientMergeInstruction::makeAction(Game &game) {}

void
RemoteClientMergeInstruction::fillPacketWithInstructionsToSend(Packet &packet,
                                                               ClientProtocol &protocol) {
  protocol.fillPacketWithMergeMessage(packet, from1, from2, to);
}


RemoteClientSameChessmanInstruction::RemoteClientSameChessmanInstruction
        (std::list<Position> &&positions_) :
        positions(std::move(positions_)) {}

void RemoteClientSameChessmanInstruction::makeAction(Game &game) {
  game.quantumTiles(positions);
}

void
RemoteClientSameChessmanInstruction::fillPacketWithInstructionsToSend(
        Packet &packet,
        ClientProtocol &protocol) {
  protocol.fillPacketWithSameChessmanInstruction(packet, *positions.begin());
}

RemoteClientEntangledChessmanInstruction::RemoteClientEntangledChessmanInstruction
        (std::list<Position>
         &&positions_) : positions(std::move(positions_)) {}

void RemoteClientEntangledChessmanInstruction::makeAction(Game &game) {
  game.entangledTiles(positions);
}

void
RemoteClientEntangledChessmanInstruction::fillPacketWithInstructionsToSend(
        Packet &packet,
        ClientProtocol &protocol) {
  protocol.fillPacketWithEntangledChessmanInstruction(packet,
                                                      *positions.begin());
}

RemoteClientSoundInstruction::RemoteClientSoundInstruction(uint8_t sound_) :
        sound(sound_) {}

void RemoteClientSoundInstruction::makeAction(Game &game) {
  switch (sound) {
    case SPLIT_SOUND:
      game.playSplitSound();
      break;
    case MERGE_SOUND:
      game.playMergeSound();
      break;
    case CAPTURE_SOUND:
      game.playCaptureSound();
      break;
  }
}

void
RemoteClientSoundInstruction::fillPacketWithInstructionsToSend(
        Packet &packet,
        ClientProtocol &protocol) {}

RemoteClientLogInstruction::RemoteClientLogInstruction(
        std::list<std::string> &&log_)
        : log(std::move(log_)) {
}

void RemoteClientLogInstruction::makeAction(Game &game) {
  for (auto &entry: log) {
    std::cout << entry << std::endl;
  }
}

void
RemoteClientLogInstruction::fillPacketWithInstructionsToSend(Packet &packet,
                                                             ClientProtocol &protocol) {}


