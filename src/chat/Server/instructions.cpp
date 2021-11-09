#include "instructions.h"
#include "blocking_queue.h"

void Instruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {

}

void Instruction::fillPacketWithInstructionsToSend(Packet& packet) {

}

ChatInstruction::ChatInstruction(std::string&& message)
                :message(std::move(message)) {
}


void ChatInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {
    //Do something with the chat (is there a chat in the server?)
    //Notify all queues
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ChatInstruction>(std::move(this->message));
    std::list<BlockingQueue>::iterator it;
    for (it = listening_queues.begin(); it != listening_queues.end(); it++)
        (*it).push(this_instruc_ptr);
}

void ChatInstruction::fillPacketWithInstructionsToSend(Packet& packet) {
    packet.addByte('c');
    packet.addBytes(this->message);
}

void MovementInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {

}

void MovementInstruction::fillPacketWithInstructionsToSend(Packet& packet) {

}
