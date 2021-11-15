#ifndef QUANTUM_CHESS_PROJ_INSTRUCTION_H
#define QUANTUM_CHESS_PROJ_INSTRUCTION_H

#include <string>
#include <list>
#include "common_packet.h"
#include "nick_names_repository.h"
#include "server_protocol.h"
#include <vector>

#define MATCH_ID -1

class ServerProtocol;

class BlockingQueue;

class ClientHandler;

class Instruction {
private:


public:
    Instruction() = default;

    //Given the list of listening queues and the client's vector, it makes the appropiate action
    //and notifies all queues of the changes.
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                       std::vector<ClientHandler>& clients);

    //The derived Instruction class asks the protocol to fill the given packet with the information
    //accordingly.
    virtual void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                  const NickNamesRepository& nick_names,
                                                  const int& client_receiver_id) = 0;

    ~Instruction() = default;
};

class ChatInstruction: public Instruction {
private:
    const int instructor_id;
    std::string message;

public:
    ChatInstruction() = delete;

    //Creates a ChatInstruction, saving the client_id and message passed to the function parameters.
    ChatInstruction(const int& client_id, std::string&& message);

    //Creates a new ChatInstruction and sends it to all listening queues.
    void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                       std::vector<ClientHandler>& clients);

    //Gets the instructor's nickname from the NickNamesRepository using the object's instructor_id
    //attribute, and calls the protocol method fillPacketWithChatInfo to fill the given packet.
    void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                  const NickNamesRepository& nick_names,
                                                  const int& client_receiver_id);

    ~ChatInstruction() = default;
};

class ExitInstruction: public Instruction {
private:
    const int instructor_id;

public:
    ExitInstruction() = delete;

    //Creates a new ExitInstruction, saving the client_id (that is the instrcuctor's id).
    ExitInstruction(const int& client_id);

    //It creates a new ExitInstruction and sends it to all the listening queues (even to the leaving
    //client queue), and joins the ClientHandler that corresponds to the object's instructor_id.
    //If the instructor's id is the MATCH_ID, a runtime_error exception is thrown. This is useful
    //to stop the match's execution.
    void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                       std::vector<ClientHandler>& clients);

    //Gets the leaving instructor's nickname from the NickNamesRepository using the object's instructor_id
    //attribute, and calls the protocol method fillPacketWithExitInfo to fill the given packet. If the
    //client_receiver_id (this is, the id of the corresponding remote client) ìs the same as the object's
    //instructor_id (the id of the person that left), it means that the remote client is disconnected and
    //a runtime_error exception is thrown.
    void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet,
                                                  const NickNamesRepository& nick_names,
                                                  const int& client_receiver_id);

    ~ExitInstruction() = default;
};

/*
class MovementInstruction: public Instruction {
private:
    const int instructor_id;
public:
    MovementInstruction(const int& client_id);
    virtual void makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues);
    virtual void fillPacketWithInstructionsToSend(ServerProtocol& protocol, Packet& packet
                                                   const NickNamesRepository& nick_names);
};*/

#endif //QUANTUM_CHESS_PROJ_INSTRUCTION_H
