#include "login_state.h"

LoginState::LoginState()
            : connected_to_server(false), connected_to_match(false) {
}

bool LoginState::clientIsConnectedToMatch() {
    return connected_to_match;
}

Socket LoginState::getClientSocket() {
    return std::move(login.getClientSocket());
}

std::string LoginState::getClientNickName() {
    return std::move(login.getClientNickName());
}