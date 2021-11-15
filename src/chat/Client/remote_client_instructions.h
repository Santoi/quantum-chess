#ifndef QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H
#define QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H

#include <string>

class RemoteClientInstruction {
protected:
    const std::string instructor_nick_name;

public:
    RemoteClientInstruction() = delete;

    //A RemoteClientInstruction is created, saving the instructor's nick name received in the
    //function parameter.
    RemoteClientInstruction(const std::string& instructor_nick_name);

    //A RemoteClientInstruction derived class needs to implement the virtual method makeAction.
    virtual void makeAction() = 0;

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
    void makeAction();

    ~RemoteClientChatInstruction() = default;

};

class RemoteClientExitMessageInstruction: public RemoteClientInstruction {
public:
    RemoteClientExitMessageInstruction() = delete;

    //Creates a RemoteClientExitMessageInstruction saving the nick_name of the person leaving
    //passed as function parameters.
    RemoteClientExitMessageInstruction(const std::string& nick_name);

    //Prints to stdout "instructor_nick_name left the game"
    void makeAction();

    ~RemoteClientExitMessageInstruction() = default;
};

#endif //QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H
