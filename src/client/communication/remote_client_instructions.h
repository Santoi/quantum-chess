#ifndef QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H
#define QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H

#include <string>
#include <list>
#include <vector>
#include "../position.h"
#include "../ascii/ascii_board.h"
#include "../../common/src/packet.h"
#include "client_protocol.h"
#include "chessman_data.h"
#include "../game/game.h"

// TODO diferenciar las que llegan de las que se van.

class ClientProtocol;

class ChessmanData;

class RemoteClientInstruction {
protected:
    const std::string instructor_nick_name;

public:
    RemoteClientInstruction() = default;

    //A RemoteClientInstruction is created, saving the instructor's nick name received in the
    //function parameter.
    RemoteClientInstruction(const std::string& instructor_nick_name);

    virtual void fillPacketWithInstructionsToSend(Packet & packet, ClientProtocol & protocol);

    //A RemoteClientInstruction derived class needs to implement the virtual method makeAction.
    virtual void makeAction(Game &game) = 0;

    ~RemoteClientInstruction() = default;

};

class RemoteClientChatInstruction: public RemoteClientInstruction {
private:
    const std::string message;

public:
    RemoteClientChatInstruction() = delete;

    //Creates a RemoteClientChatInstruction saving the nick_name and message passed as function
    //parameters.
    RemoteClientChatInstruction(const std::string& nick_name, const std::string& message);

    //Prints to stdout "instructor_nick_name sends message"
    void makeAction(Game &game) override;

    void fillPacketWithInstructionsToSend(Packet & packet, ClientProtocol & protocol) override;

    ~RemoteClientChatInstruction() = default;
};

class RemoteClientExitMessageInstruction: public RemoteClientInstruction {
public:
    RemoteClientExitMessageInstruction() = delete;

    //Creates a RemoteClientExitMessageInstruction saving the nick_name of the person leaving
    //passed as function parameters.
    RemoteClientExitMessageInstruction(const std::string& nick_name);

    //Prints to stdout "instructor_nick_name left the game"
    void makeAction(Game &game);

    ~RemoteClientExitMessageInstruction() = default;
};

class RemoteClientLoadMessageInstruction: public RemoteClientInstruction {
    std::vector<ChessmanData> chessman_data_vector;

public:
    RemoteClientLoadMessageInstruction() = delete;

    //Creates a RemoteClientExitMessageInstruction saving the nick_name of the person leaving
    //passed as function parameters.
    RemoteClientLoadMessageInstruction(std::vector<ChessmanData> && chessman_data_vector_);

    //Prints to stdout "instructor_nick_name left the game"
    void makeAction(Game &game);

    ~RemoteClientLoadMessageInstruction() = default;
};

class RemoteClientMoveInstruction: public RemoteClientInstruction {
    Position initial;
    Position final;

public:
    RemoteClientMoveInstruction() = delete;

    RemoteClientMoveInstruction(const Position &initial_, const Position &final_);

    void makeAction(Game &game);

    void fillPacketWithInstructionsToSend(Packet & packet, ClientProtocol & protocol) override;

    ~RemoteClientMoveInstruction() = default;
};

#endif //QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H
