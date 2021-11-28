#include "login_state.h"

LoginState::LoginState()
            : connected_to_server(false), connected_to_match(false) {
}

bool LoginState::clientIsConnectedToMatch() {
    return connected_to_match;
}

void LoginState::tellRendererWhatToRender(LoginRenderer& login_renderer) const {
    if (!connected_to_server)
        login_renderer.renderIPAndPortFields();
}


Socket LoginState::getClientSocket() {
    return std::move(login.getClientSocket());
}

std::string LoginState::getClientNickName() {
    return std::move(login.getClientNickName());
}