#include "chess_exception_instruction.h"

#include "instruction.h"
#include "../../../common/src/blocking_queue.h"
#include "../client_handler.h"

ChessExceptionInstruction::ChessExceptionInstruction(
        const ClientData &instructor_data_, std::string &&message) :
        instructor_data(instructor_data_),
        message(std::move(message)) {}


void ChessExceptionInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {

  std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ChessExceptionInstruction>(
          instructor_data, std::move(this->message));
  listening_queues.at(instructor_data.id).push(this_instruc_ptr);
}

void ChessExceptionInstruction::fillPacketWithInstructionsToSend(
        ServerProtocol &protocol,
        Packet &packet,
        const ClientData &client_receiver_data) {
  protocol.fillPacketWithExceptionInfo(packet, this->message);
}