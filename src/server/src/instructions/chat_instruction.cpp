#include "chat_instruction.h"
#include "../../../common/src/blocking_queue.h"

ChatInstruction::ChatInstruction(const ClientData &instructor_data_,
                                 std::string &&message) :
        instructor_data(instructor_data_),
        message(std::move(message)) {}


void ChatInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {
  std::cout << "llegue" << std::endl;
  std::shared_ptr<Instruction> this_instruc_ptr = std::make_shared<ChatInstruction>(
          instructor_data, std::move(this->message));

  for (auto &listening_queue: listening_queues)
    listening_queue.second.push(this_instruc_ptr);
}

void ChatInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                       Packet &packet,
                                                       const ClientData &client_receiver_data) {
  // Calculate time
  protocol.fillPacketWithChatInfo(packet, instructor_data, this->message,
                                  getTimeStamp());
}

std::string ChatInstruction::getTimeStamp() {
  time_t now = time(nullptr);
  struct tm *ts = localtime(&now);
  std::string timestamp = std::to_string(ts->tm_hour) + ":" +
                          std::to_string(ts->tm_min);
  return timestamp;
}