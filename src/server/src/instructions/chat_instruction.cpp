#include "chat_instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "../client_handler.h"

ChatInstruction::ChatInstruction(const int& client_id, std::string&& message):
                                 instructor_id(client_id),
                                 message(std::move(message)) {}


void ChatInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<int, BlockingQueue<Instruction>> &listening_queues,
        std::map<int, ClientHandler>& clients, Board & board,
        BlockingQueue<Instruction> & match_updates_queue) {
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ChatInstruction>(this->instructor_id, std::move(this->message));
    for (auto it = listening_queues.begin(); it != listening_queues.end(); it++)
        it->second.push(this_instruc_ptr);
}

void ChatInstruction::fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                       const NickNamesRepository& nick_names,
                                                       const int& client_receiver_id) {
    std::string nick_name;
    nick_names.getNickNameRelatedToId(nick_name, this->instructor_id);
    protocol.fillPacketWithChatInfo(packet, nick_name, this->message);
}