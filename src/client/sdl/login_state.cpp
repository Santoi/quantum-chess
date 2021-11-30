#include "login_state.h"
#include "../../common/src/unique_ptr.h"

LoginState::LoginState(Login& login_)
            :login(login_){
}

NotConnectedToServerState::NotConnectedToServerState(Login& login_, Renderer& renderer_)
                            :LoginState(login_) {
    text_entry_buttons_ptr.reserve(2);
    std::unique_ptr<TextEntryButton> ip_ptr = make_unique<TextEntryButton>(renderer_, "img/buttons/ip_text.png");
    text_entry_buttons_ptr.push_back(std::move(ip_ptr));
    std::unique_ptr<TextEntryButton> port_ptr = make_unique<TextEntryButton>(renderer_, "img/buttons/port_text.png");
    text_entry_buttons_ptr.push_back(std::move(port_ptr));
    buttons_ptr.reserve(1);
    std::unique_ptr<Button> button_ptr = make_unique<ConnectButton>(renderer_, text_entry_buttons_ptr);
    buttons_ptr.push_back(std::move(button_ptr));
}

bool NotConnectedToServerState::clientIsConnectedToMatch() {
    return false;
}

void NotConnectedToServerState::tellRendererWhatToRender(LoginRenderer& login_renderer) {
    login_renderer.renderIPAndPortFields(*buttons_ptr[0], *text_entry_buttons_ptr[0],
                                         *text_entry_buttons_ptr[1]);
}

void NotConnectedToServerState::fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) {
    for (auto it = buttons_ptr.begin(); it != buttons_ptr.end(); it++)
        active_buttons.push_back(**it);
}

void NotConnectedToServerState::fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                                                active_text_entries) {
    for (auto it = text_entry_buttons_ptr.begin(); it != text_entry_buttons_ptr.end(); it++)
        active_text_entries.push_back(**it);
}

int NotConnectedToServerState::proccessTokens(std::list<std::string>&& tokens) {
    std::string ip = tokens.front(); //tokens strings has the same order as how TextEntryButton are in the list
                                    //(first the ip string, second the port string)
    tokens.pop_front();
    std::cout << ip << std::endl;
    std::string port = tokens.front();
    tokens.pop_front();
    std::cout << port << std::endl;
    login.connectToServer(ip, port);
    return 1;
     //pop port token, ip, name...
     //tell login to connect to socket
}

NotConnectedToMatchState::NotConnectedToMatchState(Login& login_, Renderer& renderer_)
                        :LoginState(login_) {
}

bool NotConnectedToMatchState::clientIsConnectedToMatch() {
    return true;
}

void NotConnectedToMatchState::tellRendererWhatToRender(LoginRenderer& login_renderer) {

}

void NotConnectedToMatchState::fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) {

}

void NotConnectedToMatchState::fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                                                        active_text_entries) {

}

int NotConnectedToMatchState::proccessTokens(std::list<std::string>&& tokens) {
    return 2;
}