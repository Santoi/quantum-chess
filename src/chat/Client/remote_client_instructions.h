#ifndef QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H
#define QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H

#include <string>

class RemoteClientInstruction {
protected:
    const std::string instructor_nick_name;

public:
    RemoteClientInstruction() = delete;
    RemoteClientInstruction(const std::string& instructor_nick_name);
    virtual void makeAction() = 0;
    ~RemoteClientInstruction() = default;

};

class RemoteClientChatInstruction: public RemoteClientInstruction {
private:
    const std::string message;

public:
    RemoteClientChatInstruction() = delete;
    RemoteClientChatInstruction(const std::string& nick_name, const std::string& message);
    void makeAction();
    ~RemoteClientChatInstruction() = default;

};

class RemoteClientExitMessageInstruction: public RemoteClientInstruction {
private:

public:
    RemoteClientExitMessageInstruction() = delete;
    RemoteClientExitMessageInstruction(const std::string& nick_name);
    void makeAction();
    ~RemoteClientExitMessageInstruction() = default;

};

#endif //QUANTUM_CHESS_PROJ_REMOTE_CLIENT_INSTRUCTIONS_H
