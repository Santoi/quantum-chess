#include "chess_exception_instruction.h"

#include "instruction.h"
#include "../../../common/blocking_queue.h"
#include "../client_handler.h"

ChessExceptionInstruction::ChessExceptionInstruction(
        const ClientData &instructor_data_, std::string &&message) :
        instructor_data(instructor_data_),
        message(std::move(message)) {}


void ChessExceptionInstruction::makeActionAndNotify(Match &match) {}

void ChessExceptionInstruction::fillPacketWithInstructionToSend(
        ServerProtocol &protocol,
        Packet &packet,
        const ClientData &client_receiver_data) {
  protocol.fillPacketWithExceptionMessage(packet, this->message);
}
