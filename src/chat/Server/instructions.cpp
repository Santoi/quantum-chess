#include "instructions.h"
#include "blocking_queue.h"
#include <arpa/inet.h>
#include <exception>
#include "client_handler.h"

#define MATCH_ID -1

void Instruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                        std::vector<ClientHandler>& clients) {

}

void Instruction::fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                   const NickNamesRepository& nick_names,
                                                   const int& client_receiver_id) {

}

ChatInstruction::ChatInstruction(const int& client_id, std::string&& message)
                :instructor_id(client_id), message(std::move(message)) {
}


void ChatInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                            std::vector<ClientHandler>& clients) {
    //Do something with the chat (is there a chat in the server?)
    //Notify all queues
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

ExitInstruction::ExitInstruction(const int& client_id)
                :instructor_id(client_id) {
}

void ExitInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                            std::vector<ClientHandler>& clients) {
    if (this->instructor_id == MATCH_ID)
        throw std::runtime_error("");
    //Just notify existing queues that the player left the game
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ExitInstruction>(this->instructor_id);
    std::list<BlockingQueue>::iterator it;
    for (it = listening_queues.begin(); it != listening_queues.end(); it++)
        (*it).push(this_instruc_ptr);
    clients[this->instructor_id].join();
}

void ExitInstruction::fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                       const NickNamesRepository& nick_names,
                                                       const int& client_receiver_id) {
    if (this->instructor_id == client_receiver_id)
        throw std::runtime_error("");
    std::string leaving_client_nick_name;
    nick_names.getNickNameRelatedToId(leaving_client_nick_name, this->instructor_id);
    protocol.fillPacketWithExitInfo(packet, leaving_client_nick_name);
}

/*
void MovementInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {

}

void MovementInstruction::fillPacketWithInstructionsToSend(Packet& packet) {

}*/
