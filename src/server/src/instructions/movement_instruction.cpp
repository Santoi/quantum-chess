#include "movement_instruction.h"
#include "load_board_instruction.h"

MovementInstruction::MovementInstruction(const int& client_id,
                                     const Position & initial_,
                                     const Position & final_):
                                     instructor_id(client_id),
                                     initial(initial_), final(final_) {}


void MovementInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue<Instruction>>& listening_queues,
                                                            std::vector<ClientHandler>& clients,
                                                            Board & board, BlockingQueue<Instruction> & match_updates_queue) {
    // TODO validar color, permisos, etc
    board.move(initial, final);
    LoadBoardInstruction instruction;
    match_updates_queue.push(
            std::make_shared<LoadBoardInstruction>(instruction));
}

void MovementInstruction::fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                       const NickNamesRepository& nick_names,
                                                       const int& client_receiver_id) {
    /*std::string nick_name;
    nick_names.getNickNameRelatedToId(nick_name, this->instructor_id);
    protocol.fillPacketWithChatInfo(packet, nick_name, this->message);*/
}