#include "log_instruction.h"
#include "../../../common/src/blocking_queue.h"

LogInstruction::LogInstruction(std::list<std::string> &&log_) :
        log(std::move(log_)) {}


void LogInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {
  std::shared_ptr<Instruction> this_instruct_ptr = std::make_shared<LogInstruction>(
          std::move(log));

  for (auto &listening_queue: listening_queues)
    listening_queue.second.push(this_instruct_ptr);
}

void LogInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                      Packet &packet,
                                                      const ClientData &client_receiver_data) {
  protocol.fillPacketLogInstruction(packet, log);
}