#ifndef QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H
#define QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H

#include <string>
#include "../../common/src/socket.h"
#include "../../common/src/protocol.h"
#include "remote_client_instructions.h"
#include "../../common/src/client_data.h"
#include <memory>

class RemoteClientInstruction;

class ClientProtocol: public Protocol {
public:
    ClientProtocol() = default;

    //Given the client socket, it returns the number of games running in server.
    std::map<uint16_t, std::vector<ClientData>> receiveMatchesInfo(Socket& socket);

    //It sends to the client socket the game_number received as parameter.
    void sendChosenGame(Socket& socket, uint16_t game_number);

    //It sends to the client socket the client's nick_name, following the protocol.
    void sendClientsNickName(Socket& socket, std::string& nick_name);

    void fillPacketWithChatMessage(Packet &packet, const std::string & message);

    //Following the protocol, it receives from socket the information necessary to create the
    //appropiate RemoteClientInstruction. After the function ends, the ptr_instruction points to a
    //valid instruction that can be executed calling the makeAction instruction.
    void receiveInstruction(Socket& socket, std::shared_ptr<RemoteClientInstruction>& ptr_instruction);

    void sendInstruction(Socket &socket,
                         std::shared_ptr<RemoteClientInstruction> &instruction);

    ~ClientProtocol() = default;

    void
    fillPacketWithMoveMessage(Packet &packet, Position &initial,
                              Position &final);

private:
    //Gets necessary information to create the RemoteClientChatInstruction (the instructor's nick
    //name and the corresponding message). After the function ends, the ptr_instruction points to this
    //new ChatInstruction.
    void fillClientInstructionWithChat(Socket& socket, std::shared_ptr<RemoteClientInstruction>&
                                                        ptr_instruction);

    //Gets necessary information to create the RemoteClientExitMessageInstruction (the instructor's nick
    //name, this is, the person that left the match). After the function ends, the ptr_instruction
    //points to this new ExitInstruction.
    void fillClientInstructionWithExitMessage(Socket& socket, std::shared_ptr<RemoteClientInstruction>&
                                                             ptr_instruction);

    void fillClientInstructionWithLoadBoard(Socket &socket,
                                            std::shared_ptr<RemoteClientInstruction> &ptr_instruction);

};

#endif //QUANTUM_CHESS_PROJ_CLIENT_PROTOCOL_H
