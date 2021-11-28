#include "login_state.h"

LoginState::LoginState(Login& login_)
            :login(login_){
}


NotConnectedToServerState::NotConnectedToServerState(Login& login_)
                            :LoginState(login_) {
    Button ipButton;
    buttons.push_back(std::move(ipButton));
    Button portButton;
    buttons.push_back(std::move(portButton));
    Button connectButton;
    buttons.push_back(std::move(connectButton));
}

bool NotConnectedToServerState::clientIsConnectedToMatch() {
    return false;
}

void NotConnectedToServerState::tellRendererWhatToRender(LoginRenderer& login_renderer) {
    login_renderer.renderIPAndPortFields(buttons);
}

void NotConnectedToServerState::fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) {
    for (auto it = buttons.begin(); it != buttons.end(); it++)
        active_buttons.push_back(*it);
}

void NotConnectedToServerState::proccessTokens(const std::list<std::string>& tokens) {
     //pop port token, ip, name...
     //tell login to connect to socket
}
