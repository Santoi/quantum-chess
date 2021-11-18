#include "exit_instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "../client_handler.h"
#include "../quantum_chess/board.h"

ExitInstruction::ExitInstruction(const int& client_id)
        :instructor_id(client_id) {
}

void ExitInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<int, BlockingQueue<Instruction>> &listening_queues,
        std::map<int, ClientHandler>& clients,
        Board & board, BlockingQueue<Instruction> & match_updates_queue) {
    if (this->instructor_id == MATCH_ID)
        throw std::runtime_error("");
    //Just notify existing queues that the player left the game
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ExitInstruction>(
            this->instructor_id);
    auto it_queue = listening_queues.begin();
    auto it_client = clients.begin();
    for (; it_queue != listening_queues.end() && it_client != clients.end(); ) {
        // TODO estoy suponiendo que estan en el mismo orden.
        if (it_queue->first == instructor_id) {
            it_client->second.stop();
            it_client->second.join();
            std::cout << "hola" << std::endl;
            it_client = clients.erase(it_client);
            it_queue = listening_queues.erase(it_queue);
            continue;
        }
        it_queue->second.push(this_instruc_ptr);
        ++it_queue; ++it_client;
    }
}

void ExitInstruction::fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                       const NickNamesRepository& nick_names,
                                                       const int& client_receiver_id) {
    // TODO ver cuando revise lo de matar los clientes cuando se van desconectando.
    if (this->instructor_id == client_receiver_id)
        return;
    std::string leaving_client_nick_name;
    nick_names.getNickNameRelatedToId(leaving_client_nick_name, this->instructor_id);
    protocol.fillPacketWithExitInfo(packet, leaving_client_nick_name);
}