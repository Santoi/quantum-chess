#include "surrender_instruction.h"

SurrenderInstruction::SurrenderInstruction(const ClientData &instructor_data_)
                    :instructor_data(instructor_data_) {
}

void SurrenderInstruction::makeActionAndNotify(Match &match) {
  //match.end()
  //update event log
}


void
fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                const ClientData &client_receiver_data) {
  //
}

