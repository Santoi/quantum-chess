#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_H

#include "login_renderer.h"
#include "login.h"
#include "button.h"
#include <atomic>
#include <list>

class LoginRenderer;

class LoginState {
protected:
    Login& login;
    std::list<Button> buttons;

public:

    LoginState() = delete;

    LoginState(Login& login_);

    virtual bool clientIsConnectedToMatch() = 0;

    virtual void tellRendererWhatToRender(LoginRenderer& login_renderer) = 0;

    virtual void fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) = 0;

    virtual void proccessTokens(const std::list<std::string>& tokens) = 0;
};

class NotConnectedToServerState: public LoginState {
public:

    NotConnectedToServerState(Login& login_);

    bool clientIsConnectedToMatch() override;

    void tellRendererWhatToRender(LoginRenderer& login_renderer) override;

    void fillWithActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons) override;

    void proccessTokens(const std::list<std::string>& tokens) override;
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_H
