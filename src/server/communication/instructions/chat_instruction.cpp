#include "chat_instruction.h"
#include "../../../common/blocking_queue.h"
#include <string>

ChatInstruction::ChatInstruction(const ClientData &instructor_data_,
                                 std::string &&message) :
    instructor_data(instructor_data_),
    message(std::move(message)) {}


void ChatInstruction::makeActionAndNotify(Match &match) {
  auto this_instruct_ptr = std::make_shared<ChatInstruction>(
      instructor_data, std::move(this->message));
  match.addInstrToAllListeningQueues(this_instruct_ptr);
}

void ChatInstruction::
fillPacketWithInstructionToSend(ServerProtocol &protocol,
                                Packet &packet,
                                const ClientData &client_receiver_data) {
  // Calculate time
  protocol.fillPacketWithChatMessage(packet, instructor_data, this->message,
                                     getTimeStamp());
}

std::string ChatInstruction::getTimeStamp() {
  time_t now = time(nullptr);
  struct tm *ts = localtime(&now);
  std::string hour = std::to_string(ts->tm_hour);
  std::string min = std::to_string(ts->tm_min);
  // Formatting for 00
  if (hour.size() == 1)
    hour = "0" + hour;
  if (min.size() == 1)
    min = "0" + min;
  std::string timestamp = hour + ":" + min;
  return timestamp;
}
