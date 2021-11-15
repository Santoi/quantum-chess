#include "chat_instruction.h"
#include "../blocking_queue.h"
#include "../client_handler.h"

ChatInstruction::ChatInstruction(const int& client_id, std::string&& message)
        :instructor_id(client_id), message(std::move(message)) {
}


void ChatInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                            std::vector<ClientHandler>& clients) {
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ChatInstruction>(this->instructor_id, std::move(this->message));
    std::list<BlockingQueue>::iterator it;
    for (it = listening_queues.begin(); it != listening_queues.end(); it++)
        (*it).push(this_instruc_ptr);
}

void ChatInstruction::fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                       const NickNamesRepository& nick_names,
                                                       const int& client_receiver_id) {
    std::string nick_name;
    nick_names.getNickNameRelatedToId(nick_name, this->instructor_id);
    protocol.fillPacketWithChatInfo(packet, nick_name, this->message);
}