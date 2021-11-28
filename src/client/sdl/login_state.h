#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_H

#include "login.h"
#include "login_renderer.h"
#include "button.h"
#include <atomic>
#include <list>

class LoginRenderer;

class LoginState {
private:
    Login login;
    std::atomic<bool> connected_to_server;
    std::atomic<bool> connected_to_match;
    Button connect_button;
    Button select_ip_text_field;
    Button select_port_text_field;

public:
    LoginState();

    bool clientIsConnectedToMatch();

    void tellRendererWhatToRender(LoginRenderer& login_renderer) const;

    void getActiveButtons(std::list<std::reference_wrapper<Button>>& active_buttons);

    void proccessTokens(const std::list<std::string>& tokens);

    Socket getClientSocket();

    std::string getClientNickName();
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_H
