#include "surrender_instruction.h"

SurrenderInstruction::SurrenderInstruction(const ClientData &instructor_data_)
                    :instructor_data(instructor_data_) {
}

void SurrenderInstruction::makeActionAndNotify(Match &match) {
  //match.end()
  std::cout << "notifying listening queues" << std::endl;
  std::shared_ptr<Instruction> this_instruct_ptr = std::make_shared<SurrenderInstruction>(
                                                          instructor_data);
  match.addInstrToAllListeningQueues(this_instruct_ptr);
}


void SurrenderInstruction::fillPacketWithInstructionToSend(ServerProtocol &protocol,
                                                           Packet &packet,
                                                           const ClientData &client_receiver_data) {
  std::cout << "sending packet to client" << client_receiver_data.id << std::endl;
  protocol.fillPacketWithSurrenderMessage(packet, instructor_data, getTimeStamp());
}

std::string SurrenderInstruction::getTimeStamp() {
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
