#ifndef QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H

#include "handler_thread.h"
#include "login_state_handler.h"
#include "pixel_coordinate.h"
#include <SDL2/SDL.h>
#include <atomic>

class LoginHandlerThread : public HandlerThread {
private:
    PixelCoordinate last_click;
    SDL_Event event;
    LoginStateHandler& login_state_handler;
    bool expecting_text_entry;

public:
    LoginHandlerThread() = delete;

    LoginHandlerThread(LoginStateHandler& login_state_handler_);

    // Event loop
    void run() override;

    ~LoginHandlerThread() = default;

private:
    void handleMouseButtonLeft(SDL_MouseButtonEvent &mouse);
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_HANDLER_THREAD_H
