#ifndef QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H
#define QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H

#include "scene.h"
#include "window.h"
#include "login_state.h"

class LoginState;

class LoginRenderer: public Scene {
private:
    const LoginState& login_state;

public:

    LoginRenderer() = delete;

    LoginRenderer(const LoginState& login_state_, Window& window);

    void render();

    void renderIPAndPortFields();

    void setScale(int scale_);
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H
