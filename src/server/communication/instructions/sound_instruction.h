#ifndef QUANTUM_CHESS_PROJ_SOUND_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_SOUND_INSTRUCTION_H

#include "instruction.h"
#include "../../quantum_chess/board.h"

#define SPLIT_SOUND 0
#define MERGE_SOUND 1
#define CAPTURE_SOUND 2


class SoundInstruction : public Instruction {
private:
  uint8_t sound;

public:
  SoundInstruction() = delete;

  //Creates a ChatInstruction, saving the client_id and message passed to the function parameters.
  explicit SoundInstruction(uint8_t sound_);

  // Does nothing
  void makeActionAndNotify(Match &match) override;

  //Gets the instructor's nickname from the ClientDataRepository using the object's instructor_id
  //attribute, and calls the protocol method fillPacketWithChatMessage to fill the given packet.
  void
  fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                  const ClientData &client_receiver_data) override;

  ~SoundInstruction() override = default;
};


#endif //QUANTUM_CHESS_PROJ_SOUND_INSTRUCTION_H
