#ifndef QUANTUM_CHESS_SRC_SURRENDER_INSTRUCTION_H
#define QUANTUM_CHESS_SRC_SURRENDER_INSTRUCTION_H

#include "../../../common/client_data.h"
#include "instruction.h"

class SurrenderInstruction: public Instruction {
    const ClientData &instructor_data;

public:
    SurrenderInstruction() = delete;

    explicit SurrenderInstruction(const ClientData &instructor_data);

    void makeActionAndNotify(Match &match) override;

    void
    fillPacketWithInstructionToSend(ServerProtocol &protocol, Packet &packet,
                                    const ClientData
                                    &client_receiver_data) override;
};


#endif //QUANTUM_CHESS_SRC_SURRENDER_INSTRUCTION_H
