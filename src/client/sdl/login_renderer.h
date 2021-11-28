#ifndef QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H
#define QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H

#include "scene.h"
#include "window.h"

class LoginRenderer: public Scene {
private:


public:

    LoginRenderer() = delete;

    LoginRenderer(Window& window);

    void render();

    void setScale(int scale_);
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_RENDERER_H
