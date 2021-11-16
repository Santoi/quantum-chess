#ifndef QUANTUM_CHESS_PROJ_CHAT_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_CHAT_INSTRUCTION_H

#include "instruction.h"
#include "../quantum_chess/board.h"

class ChatInstruction: public Instruction {
private:
    const int instructor_id;
    std::string message;

public:
    ChatInstruction() = delete;

    //Creates a ChatInstruction, saving the client_id and message passed to the function parameters.
    ChatInstruction(const int& client_id, std::string&& message);

    //Creates a new ChatInstruction and sends it to all listening queues.
    void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue<Instruction>>& listening_queues,
                                               std::vector<ClientHandler>& clients,
                                               Board & board) override;

    //Gets the instructor's nickname from the NickNamesRepository using the object's instructor_id
    //attribute, and calls the protocol method fillPacketWithChatInfo to fill the given packet.
    void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                          const NickNamesRepository& nick_names,
                                          const int& client_receiver_id) override;

    ~ChatInstruction() = default;
};


#endif //QUANTUM_CHESS_PROJ_CHAT_INSTRUCTION_H
