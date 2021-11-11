#include "instructions.h"
#include "blocking_queue.h"
#include <arpa/inet.h>



void Instruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {

}

void Instruction::fillPacketWithInstructionsToSend(Packet& packet, const NickNamesRepository& nick_names) {

}

ChatInstruction::ChatInstruction(const int& client_id, std::string&& message)
                :instructor_id(client_id), message(std::move(message)) {
}


void ChatInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {
    //Do something with the chat (is there a chat in the server?)
    //Notify all queues
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ChatInstruction>(this->instructor_id, std::move(this->message));
    std::list<BlockingQueue>::iterator it;
    for (it = listening_queues.begin(); it != listening_queues.end(); it++)
        (*it).push(this_instruc_ptr);
}

void ChatInstruction::fillPacketWithInstructionsToSend(Packet& packet, const NickNamesRepository& nick_names) {
    packet.addByte('c');
    std::string nick_name;
    nick_names.getNickNameRelatedToId(nick_name, this->instructor_id);
    uint16_t host_length = nick_name.size();
    uint16_t lengthBE = htons(host_length);
    packet.addBytes(lengthBE);
    packet.addBytes(nick_name);

    host_length = this->message.size();
    lengthBE = htons(host_length);
    packet.addBytes(lengthBE);
    packet.addBytes(this->message);
}
/*
void MovementInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {

}

void MovementInstruction::fillPacketWithInstructionsToSend(Packet& packet) {

}*/
