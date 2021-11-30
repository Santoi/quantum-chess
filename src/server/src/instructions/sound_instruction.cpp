#include "sound_instruction.h"
#include "../../../common/src/blocking_queue.h"

SoundInstruction::SoundInstruction(uint8_t sound_) : sound(sound_) {}


void SoundInstruction::makeActionAndNotifyAllListeningQueues(
        std::map<uint16_t, BlockingQueue<Instruction>> &listening_queues,
        Match &match, BlockingQueue<Instruction> &match_updates_queue) {}

void
SoundInstruction::fillPacketWithInstructionsToSend(ServerProtocol &protocol,
                                                   Packet &packet,
                                                   const ClientData &client_receiver_data) {
  protocol.fillPacketWithSoundInfo(packet, sound);
}