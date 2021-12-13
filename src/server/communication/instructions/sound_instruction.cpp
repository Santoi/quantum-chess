#include "sound_instruction.h"
#include "../../../common/blocking_queue.h"

SoundInstruction::SoundInstruction(uint8_t sound_) : sound(sound_) {}


void SoundInstruction::makeActionAndNotify(Match &match) {}

void
SoundInstruction::fillPacketWithInstructionToSend(ServerProtocol &protocol,
                                                  Packet &packet,
                                                  const ClientData
                                                  &client_receiver_data) {
  protocol.fillPacketWithSoundMessage(packet, sound);
}
