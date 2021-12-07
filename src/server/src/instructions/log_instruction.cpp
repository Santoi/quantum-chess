#include "log_instruction.h"
#include "../../../common/src/blocking_queue.h"

LogInstruction::LogInstruction(std::list<std::string> &&log_) :
        log(std::move(log_)) {}


void LogInstruction::makeActionAndNotify(Match &match) {}

void LogInstruction::fillPacketWithInstructionToSend(ServerProtocol &protocol,
                                                     Packet &packet,
                                                     const ClientData &client_receiver_data) {
  protocol.fillPacketLogMessage(packet, log);
}