#include "exit_instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "../client_handler.h"
#include "../quantum_chess/board.h"

ExitInstruction::ExitInstruction(const ClientData & instructor_data_)
        :instructor_data(instructor_data_) {
}

void ExitInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        std::map<uint16_t, ClientHandler>& clients,
        Board & board, BlockingQueue<Instruction> & match_updates_queue) {
    if (this->instructor_data.getId() == MATCH_ID)
        throw std::runtime_error("");
    //Just notify existing queues that the player left the game
    std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ExitInstruction>(
            this->instructor_data);
    auto it_queue = listening_queues.begin();
    auto it_client = clients.begin();
    for (; it_queue != listening_queues.end() && it_client != clients.end(); ) {
        // TODO estoy suponiendo que estan en el mismo orden.
        if (it_queue->first == instructor_data.getId()) {
            it_client->second.stop();
            it_client->second.join();
            it_client = clients.erase(it_client);
            it_queue = listening_queues.erase(it_queue);
            continue;
        }
        it_queue->second.push(this_instruc_ptr);
        ++it_queue; ++it_client;
    }
}

void ExitInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                       Packet &packet,
                                                       const ClientData &client_receiver_data) {
    // TODO ver cuando revise lo de matar los clientes cuando se van desconectando.
    if (this->instructor_data.getId() == client_receiver_data.getId())
        return;
    // TODO Hacer que muestre tambien el id.
    protocol.fillPacketWithExitInfo(packet, instructor_data.getName());
}