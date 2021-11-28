#include "login_state_handler.h"
#include "../../common/src/unique_ptr.h"

LoginStateHandler::LoginStateHandler()
                   :current_state(make_unique<NotConnectedToServerState>()){
}

bool LoginStateHandler::clientIsConnectedToMatch() {
    return current_state->clientIsConnectedToMatch();
}

void LoginStateHandler::fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) {
    current_state->fillWithActiveButtons(active_buttons);
}

void LoginStateHandler::proccessTokens(const std::list<std::string>& tokens) {
    current_state->proccessTokens(tokens);
}

void LoginStateHandler::tellRendererWhatToRender(LoginRenderer& login_renderer) {
    current_state->tellRendererWhatToRender(login_renderer);
}


Socket LoginStateHandler::getClientSocket() {
    return std::move(login.getClientSocket());
}

std::string LoginStateHandler::getClientNickName() {
    return std::move(login.getClientNickName());
}
