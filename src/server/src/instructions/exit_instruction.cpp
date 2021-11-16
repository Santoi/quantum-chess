#include "exit_instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "../client_handler.h"
#include "../quantum_chess/board.h"

ExitInstruction::ExitInstruction(const int& client_id)
        :instructor_id(client_id) {
}

void ExitInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue<Instruction>>& listening_queues,
                                                            std::vector<ClientHandler>& clients,
                                                            Board & board) {
    if (this->instructor_id == MATCH_ID)
        throw std::runtime_error("");
    //Just notify existing queues that the player left the game
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ExitInstruction>(this->instructor_id);
    std::list<BlockingQueue<Instruction>>::iterator it;
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