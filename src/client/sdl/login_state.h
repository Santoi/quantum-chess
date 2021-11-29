#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_H

#include "login_renderer.h"
#include "login.h"
#include "button.h"
#include "text_entry_button.h"
#include <atomic>
#include <list>
#include <memory>

class LoginRenderer;

class LoginState {
protected:
    Login& login;
    std::list<std::unique_ptr<Button>> buttons_ptr;
    std::list<std::unique_ptr<TextEntryButton>> text_entry_buttons_ptr;

public:

    LoginState() = delete;

    explicit LoginState(Login& login_);

    virtual bool clientIsConnectedToMatch() = 0;

    virtual void tellRendererWhatToRender(LoginRenderer& login_renderer) = 0;

    virtual void fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) = 0;

    virtual void fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                                active_text_entries) = 0;

    virtual void proccessTokens(std::list<std::string>&& tokens) = 0;
};

class NotConnectedToServerState: public LoginState {
public:

    explicit NotConnectedToServerState(Login& login_);

    bool clientIsConnectedToMatch() override;

    void tellRendererWhatToRender(LoginRenderer& login_renderer) override;

    void fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) override;

    void fillWithActiveTextEntryButtons(std::list<std::reference_wrapper<TextEntryButton>>&
                                        active_text_entries) override;

    void proccessTokens(std::list<std::string>&& tokens) override;
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_H