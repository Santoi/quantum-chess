#include "login_state_handler.h"
#include "../../common/src/unique_ptr.h"

LoginStateHandler::LoginStateHandler(Renderer& renderer_)
                    :login(), renderer(renderer_),
                     current_state(make_unique<NotConnectedToServerState>(login, renderer)) {
}

bool LoginStateHandler::clientIsConnectedToMatch() {
    std::lock_guard<std::mutex> lock_guard(mutex);
    return current_state->clientIsConnectedToMatch();
}

void LoginStateHandler::fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) {
    std::lock_guard<std::mutex> lock_guard(mutex);
    current_state->fillWithActiveButtons(active_buttons);
}

void LoginStateHandler::fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                                        active_text_entries) {
    std::lock_guard<std::mutex> lock_guard(mutex);
    current_state->fillWithActiveTextEntryButtons(active_text_entries);
}


void LoginStateHandler::proccessTokens(std::list<std::string>& tokens) {
    std::lock_guard<std::mutex> lock_guard(mutex);
    current_state.reset();
    current_state = make_unique<NotConnectedToMatchState>(login, renderer);
    //try {
     //   current_state->proccessTokens(std::move(tokens));
    //} catch (...) {
     //   //TODO handlear catchear excepción si es que, por ejemplo, se intenta conectar a una ip y puerto no válido
   // }
}

void LoginStateHandler::tellRendererWhatToRender(LoginRenderer& login_renderer) {
    std::lock_guard<std::mutex> lock_guard(mutex);
    current_state->tellRendererWhatToRender(login_renderer);
}


Socket LoginStateHandler::getClientSocket() {
    return login.getClientSocket();
}

std::string LoginStateHandler::getClientNickName() {
    return login.getClientNickName();
}
