#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_H

#include "login.h"
#include <atomic>

class LoginState {
private:
    Login login;
    std::atomic<bool> connected_to_server;
    std::atomic<bool> connected_to_match;

public:
    LoginState();

    bool clientIsConnectedToMatch();

    Socket getClientSocket();

    std::string getClientNickName();
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_H
