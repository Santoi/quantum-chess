#ifndef QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H

#include "handler_thread.h"
#include "login.h"
#include "pixel_coordinate.h"
#include <SDL2/SDL.h>
#include <atomic>

class LoginHandlerThread : public HandlerThread {
private:
    PixelCoordinate last_click;
    SDL_Event event;
    Login& login;

public:
    LoginHandlerThread() = delete;

    LoginHandlerThread(Login& login_);

    // Event loop
    void run() override;

private:
    void handleMouseButtonLeft(SDL_MouseButtonEvent &mouse);
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H
