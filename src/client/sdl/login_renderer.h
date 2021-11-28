#ifndef QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H
#define QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H

#include "scene.h"
#include "window.h"
#include "login_state_handler.h"
#include "button.h"

class LoginStateHandler;

class LoginRenderer: public Scene {
private:
    LoginStateHandler& login_state_handler;

public:

    LoginRenderer() = delete;

    LoginRenderer(LoginStateHandler& login_state_handler_, Window& window);

    void render();

    void renderIPAndPortFields(std::list<Button>& buttons);

    void setScale(int scale_);
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H
