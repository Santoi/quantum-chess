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

void LoginState::getActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) {
    if (!connected_to_server) {
        active_buttons.push_back(connect_button);
        active_buttons.push_back(select_ip_text_field);
        active_buttons.push_back(select_port_text_field);
    }

}

void LoginState::proccessTokens(const std::list<std::string>& tokens) {
    if (!connected_to_server) {
        //pop port token, ip, name...
        //tell login to connect to socket
    }

}

Socket LoginState::getClientSocket() {
    return std::move(login.getClientSocket());
}

std::string LoginState::getClientNickName() {
    return std::move(login.getClientNickName());
}