#ifndef QUANTUM_CHESS_PROJ_EXIT_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_EXIT_INSTRUCTION_H

#include <string>
#include <list>
#include "../../../common/src/packet.h"
#include "../nick_names_repository.h"
#include "../server_protocol.h"
#include <vector>

class ExitInstruction: public Instruction {
private:
    const int instructor_id;

public:
    ExitInstruction() = delete;

    //Creates a new ExitInstruction, saving the client_id (that is the instrcuctor's id).
    explicit ExitInstruction(const int& client_id);

    //It creates a new ExitInstruction and sends it to all the listening queues (even to the leaving
    //client queue), and joins the ClientHandler that corresponds to the object's instructor_id.
    //If the instructor's id is the MATCH_ID, a runtime_error exception is thrown. This is useful
    //to stop the match's execution.
    void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                               std::vector<ClientHandler>& clients) override;

    //Gets the leaving instructor's nickname from the NickNamesRepository using the object's instructor_id
    //attribute, and calls the protocol method fillPacketWithExitInfo to fill the given packet. If the
    //client_receiver_id (this is, the id of the corresponding remote client) ìs the same as the object's
    //instructor_id (the id of the person that left), it means that the remote client is disconnected and
    //a runtime_error exception is thrown.
    void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                          const NickNamesRepository& nick_names,
                                          const int& client_receiver_id) override;

    ~ExitInstruction() = default;
};


#endif //QUANTUM_CHESS_PROJ_EXIT_INSTRUCTION_H
