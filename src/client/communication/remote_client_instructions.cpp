#include "remote_client_instructions.h"
#include "client_protocol.h"
#include "../position.h"
#include "../game/game.h"
#include <iostream>


RemoteClientInstruction::RemoteClientInstruction(const std::string& instructor_nick_name)
                        :instructor_nick_name(instructor_nick_name) {
}

void RemoteClientInstruction::fillPacketWithInstructionsToSend(Packet &packet,
                                                               ClientProtocol & protocol) {

}


RemoteClientChatInstruction::RemoteClientChatInstruction(const std::string& nick_name,
                                                         const std::string& message)
                            :RemoteClientInstruction(nick_name), message(message) {
}

void RemoteClientChatInstruction::makeAction(Game &game) {
    std::cout << this->instructor_nick_name << " envia: " << this->message << std::endl;
}

void RemoteClientChatInstruction::fillPacketWithInstructionsToSend(Packet &packet, ClientProtocol & protocol) {
    protocol.fillPacketWithChatMessage(packet, message);
}

RemoteClientExitMessageInstruction::RemoteClientExitMessageInstruction(const std::string& nick_name)
                                        :RemoteClientInstruction(nick_name) {
}


void RemoteClientExitMessageInstruction::makeAction(Game &game) {
    std::cout << this->instructor_nick_name << " se fue de la partida." << std::endl;
}

RemoteClientLoadMessageInstruction::RemoteClientLoadMessageInstruction(std::vector<ChessmanData> && chessman_data_vector_):
chessman_data_vector(std::move(chessman_data_vector_)){}

void RemoteClientLoadMessageInstruction::makeAction(Game &game) {
   game.load(chessman_data_vector);
}

RemoteClientMoveInstruction::RemoteClientMoveInstruction(const Position &initial_,
                                                         const Position &final_): initial(initial_), final(final_) {}

void RemoteClientMoveInstruction::makeAction(Game &game) {

}

void
RemoteClientMoveInstruction::fillPacketWithInstructionsToSend(Packet &packet,
                                                              ClientProtocol &protocol) {
    protocol.fillPacketWithMoveMessage(packet, initial, final);
}



