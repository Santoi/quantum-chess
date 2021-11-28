#include "login_handler_thread.h"
#include "button.h"
#include <list>

LoginHandlerThread::LoginHandlerThread(LoginStateHandler& login_state_handler_)
                    :HandlerThread(true), login_state_handler(login_state_handler_) {
}

void LoginHandlerThread::run() {
    while (!(login_state_handler.clientIsConnectedToMatch())) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                return;
            case SDL_MOUSEBUTTONDOWN:
                SDL_MouseButtonEvent mouse = event.button;
                if (mouse.button == SDL_BUTTON_LEFT)
                    handleMouseButtonLeft(mouse);
        }
    }
    open = false;
}

void LoginHandlerThread::handleMouseButtonLeft(SDL_MouseButtonEvent &mouse) {
    PixelCoordinate pixel(mouse.x, mouse.y);
    std::list<std::reference_wrapper<Button>> active_buttons;
    login_state_handler.fillWithActiveButtons(active_buttons);
    auto it = active_buttons.begin();
    std::list<std::string> tokens;
    while (!(it->get().fillTokensIfClicked(pixel, tokens)) && (it != active_buttons.end()))

    if (it == active_buttons.end())
        return;
    login_state_handler.proccessTokens(tokens);
}

