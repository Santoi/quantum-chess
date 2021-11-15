#include "remote_client_instructions.h"
#include <iostream>


RemoteClientInstruction::RemoteClientInstruction(const std::string& instructor_nick_name)
                        :instructor_nick_name(instructor_nick_name) {
}


RemoteClientChatInstruction::RemoteClientChatInstruction(const std::string& nick_name,
                                                         const std::string& message)
                            :RemoteClientInstruction(nick_name), message(message) {
}

void RemoteClientChatInstruction::makeAction() {
    std::cout << this->instructor_nick_name << " envia: " << this->message << std::endl;
}

RemoteClientExitMessageInstruction::RemoteClientExitMessageInstruction(const std::string& nick_name)
                                        :RemoteClientInstruction(nick_name) {
}


void RemoteClientExitMessageInstruction::makeAction() {
    std::cout << this->instructor_nick_name << " se fue de la partida." << std::endl;
}
