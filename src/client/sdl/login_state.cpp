#include "login_state.h"
#include "../../common/src/unique_ptr.h"

LoginState::LoginState(Login& login_)
            :login(login_){
}


NotConnectedToServerState::NotConnectedToServerState(Login& login_)
                            :LoginState(login_) {
    std::unique_ptr<TextEntryButton> ip_ptr = make_unique<TextEntryButton>();
    text_entry_buttons_ptr.push_back(std::move(ip_ptr));
    std::unique_ptr<TextEntryButton> port_ptr = make_unique<TextEntryButton>();
    text_entry_buttons_ptr.push_back(std::move(port_ptr));
    std::unique_ptr<Button> button_ptr = make_unique<ConnectButton>(text_entry_buttons_ptr);
    buttons_ptr.push_back(std::move(button_ptr));
}

bool NotConnectedToServerState::clientIsConnectedToMatch() {
    return false;
}

void NotConnectedToServerState::tellRendererWhatToRender(LoginRenderer& login_renderer) {
   // login_renderer.renderIPAndPortFields(buttons_ptr);
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

void NotConnectedToServerState::proccessTokens(const std::list<std::string>& tokens) {
     //pop port token, ip, name...
     //tell login to connect to socket
}
