#ifndef QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H

#include "common_socket.h"
#include "common_packet.h"
#include "instructions.h"
#include "nick_names_repository.h"
#include "protocol.h"
#include <memory>
#include "protocol.h"

class Instruction;


class ServerProtocol: public Protocol {
public:

    ServerProtocol() = default;

    //Sends to the socket the number of games running max_games.
    void sendNumberOfGamesRunning(Socket& socket, const int& max_games);

    //Receives from socket the number of the chosen game and returns it.
    int receiveNumberOfChosenGame(Socket& socket);

    //Receives from socket the remote client's nick name, storing it in the nick_name parameter.
    void getNickName(Socket& socket, std::string& nick_name);

    //Receives instructions from socket following the protocol, and creates a new Instruction derived
    //object appropiately, using the client_id and other information. By the end of the function, the
    //instruct_ptr points to this new instruction.
    void fillInstructions(Socket& socket, const int& client_id, std::shared_ptr<Instruction>& instruct_ptr);

    //Given a instruc_ptr, the function fillPacketWithInstructionsToSend is called passing the
    //nick names repository and the client id, so that the instruction knows how to get the
    //information that is needed to fill up the packet to be sent to the given socket.
    void sendPacketWithUpdates(Socket& socket, std::shared_ptr<Instruction>& instruct_ptr,
                               const NickNamesRepository& nick_names, const int& client_id);

    //Following the protocol, it fills the given packet with the chat message information. This
    //method is called by the ChatInstruction class that has the nick name and message to be
    //passed as parameters.
    void fillPacketWithChatInfo(Packet& packet, const std::string& nick_name, const std::string& message);

    //Following the protocol, it fills the given packet with the exit message information. This
    //method is called by the ExitInstruction class that has the nick name of the person leaving
    //the match.
    void fillPacketWithExitInfo(Packet& packet, const std::string& nick_name);

    ~ServerProtocol() = default;

private:
    //Creates a new ChatInstruction by receiving the message from socket and the client id passed as parameter.
    //By the end of the function, the instruc_ptr points to this new ChatInstruction object.
    void fillChatInstructions(Socket& socket, const int& client_id, std::shared_ptr<Instruction>& instruct_ptr);


    void fillMovementInstructions(Socket& socket, const int& client_id, std::shared_ptr<Instruction>& instruct_ptr);
};


#endif //QUANTUM_CHESS_PROJ_SERVER_PROTOCOL_H
