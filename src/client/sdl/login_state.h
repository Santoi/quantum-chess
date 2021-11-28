#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_H


class LoginState {
private:
    std::atomic<bool> connected_to_server;
    std::atomic<bool> connected_to_match;

public:
    LoginState();

};


#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_H
