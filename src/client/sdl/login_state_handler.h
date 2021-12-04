#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H

#include "login.h"
#include "login_state.h"
#include "renderer.h"
#include <memory>
#include <mutex>

class LoginScene;

class LoginState;

class Button;

class TextEntryButton;

class LoginStateHandler {
protected:
    Login login;
    Renderer& renderer;
    std::mutex mutex;
    std::unique_ptr<LoginState> current_state;

public:
    LoginStateHandler() = delete;

    explicit LoginStateHandler(Renderer& renderer_);

    bool clientIsConnectedToMatch();

    void fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons);

    void fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>& active_text_entries);

    void processTokens(std::list<std::string>&& tokens);

    void tellRendererWhatToRender(LoginScene& login_renderer);

    Socket getClientSocket();

    std::string getClientNickName();

    ~LoginStateHandler() = default;
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H
