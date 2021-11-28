#include "remote_client_instructions.h"
#include "client_protocol.h"
#include "../position.h"
#include "../game/game.h"
#include <iostream>


RemoteClientInstruction::RemoteClientInstruction(
        const std::string &instructor_nick_name)
        : instructor_nick_name(instructor_nick_name) {
}

void RemoteClientInstruction::fillPacketWithInstructionsToSend(Packet &packet,
                                                               ClientProtocol &protocol) {

}


RemoteClientChatInstruction::RemoteClientChatInstruction(
        const std::string &nick_name,
        const std::string &message)
        : RemoteClientInstruction(nick_name), message(message) {
}

void RemoteClientChatInstruction::makeAction(Game &game) {
  std::cout << this->instructor_nick_name << " envia: " << this->message
            << std::endl;
}

void
RemoteClientChatInstruction::fillPacketWithInstructionsToSend(Packet &packet,
                                                              ClientProtocol &protocol) {
  protocol.fillPacketWithChatMessage(packet, message);
}

RemoteClientExitMessageInstruction::RemoteClientExitMessageInstruction(
        const std::string &nick_name)
        : RemoteClientInstruction(nick_name) {
}

void RemoteClientExitMessageInstruction::makeAction(Game &game) {
  std::cout << this->instructor_nick_name << " se fue de la partida."
            << std::endl;
}

RemoteClientLoadMessageInstruction::RemoteClientLoadMessageInstruction(
        std::vector<ChessmanData> &&chessman_data_vector_) :
        chessman_data_vector(std::move(chessman_data_vector_)) {}

void RemoteClientLoadMessageInstruction::makeAction(Game &game) {
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
