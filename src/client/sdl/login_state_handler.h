#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H

#include "login.h"
#include "login_state.h"

#include <memory>

class LoginRenderer;

class LoginState;

class Button;

class TextEntryButton;

class LoginStateHandler {
protected:
    Login login;
    std::unique_ptr<LoginState> current_state;

public:
    LoginStateHandler();

    bool clientIsConnectedToMatch();

    void fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons);

    void fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>& active_text_entries);

    void proccessTokens(std::list<std::string>&& tokens);

    void tellRendererWhatToRender(LoginRenderer& login_renderer);

    Socket getClientSocket();

    std::string getClientNickName();
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H
