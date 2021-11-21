#include "movement_instruction.h"
#include "load_board_instruction.h"

MovementInstruction::MovementInstruction(const ClientData &instructor_data,
                                         const Position & initial_,
                                         const Position & final_):
                                     instructor_data(instructor_data),
                                     initial(initial_), final(final_) {}


void MovementInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        std::map<uint16_t, ClientHandler>& clients,
        Board & board, BlockingQueue<Instruction> & match_updates_queue) {
    // TODO validar color, permisos, etc
    board.move(initial, final);
    LoadBoardInstruction instruction;
    match_updates_queue.push(
            std::make_shared<LoadBoardInstruction>(instruction));
}

void
MovementInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                      Packet &packet,
                                                      const ClientData &client_receiver_data) {
    /*std::string nick_name;
    data.getClientsData(nick_name, this->instructor_id);
    protocol.fillPacketWithChatInfo(packet, nick_name, this->message);*/
}