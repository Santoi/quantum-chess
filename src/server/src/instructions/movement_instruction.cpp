#include "movement_instruction.h"

MovementInstruction::MovementInstruction(const int& client_id,
                                     const Position & initial_,
                                     const Position & final_):
                                     instructor_id(client_id),
                                     initial(initial_), final(final_) {}


void MovementInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue<Instruction>>& listening_queues,
                                                            std::vector<ClientHandler>& clients,
                                                            Board & board) {
    /*std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ChatInstruction>(this->instructor_id, std::move(this->message));
    std::list<BlockingQueue>::iterator it;
    for (it = listening_queues.begin(); it != listening_queues.end(); it++)
        (*it).push(this_instruc_ptr);*/
    // TODO validar color, permisos, etc
    board.move(initial, final);
}

void MovementInstruction::fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                       const NickNamesRepository& nick_names,
                                                       const int& client_receiver_id) {
    /*std::string nick_name;
    nick_names.getNickNameRelatedToId(nick_name, this->instructor_id);
    protocol.fillPacketWithChatInfo(packet, nick_name, this->message);*/
}