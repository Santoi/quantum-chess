#include "chat_instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "../client_handler.h"

ChatInstruction::ChatInstruction(const ClientData & instructor_data_, std::string&& message):
                                 instructor_data(instructor_data_),
                                 message(std::move(message)) {}


void ChatInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        std::map<uint16_t, ClientHandler>& clients, Board & board,
        BlockingQueue<Instruction> & match_updates_queue) {
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ChatInstruction>(instructor_data, std::move(this->message));
    for (auto it = listening_queues.begin(); it != listening_queues.end(); it++)
        it->second.push(this_instruc_ptr);
}

void ChatInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                       Packet &packet,
                                                       const ClientData &client_receiver_data) {
    // TODO agregar id.
    protocol.fillPacketWithChatInfo(packet, instructor_data.getName(), this->message);
}