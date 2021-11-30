#include "exit_instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "chat_instruction.h"

ExitInstruction::ExitInstruction(const ClientData &instructor_data_)
        : instructor_data(instructor_data_) {
}

// TODO Hacer que esto reciba match y lo borre por ahi!!
void ExitInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {
  /*if (this->instructor_data.id == MATCH_ID)
    throw std::runtime_error("");*/
  //Just notify existing queues that the player left the game
  std::shared_ptr<Instruction> this_instruc_ptr =
          std::make_shared<ExitInstruction>(instructor_data);
  match.deleteClientWithId(instructor_data.id);

  for (auto &listening_queue: listening_queues)
    listening_queue.second.push(this_instruc_ptr);

  std::shared_ptr<Instruction> chat_instruction = std::make_shared<ChatInstruction>(
          instructor_data, "has left");

  for (auto &listening_queue: listening_queues)
    listening_queue.second.push(chat_instruction);
}

void ExitInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                       Packet &packet,
                                                       const ClientData &client_receiver_data) {
  // TODO ver cuando revise lo de matar los clientes cuando se van desconectando.
  if (this->instructor_data.id == client_receiver_data.id)
    return;
  // TODO Hacer que muestre tambien el id.
  protocol.fillPacketWithExitInfo(packet, instructor_data.name);
}