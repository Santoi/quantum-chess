#include "login_handler_thread.h"

LoginHandlerThread::LoginHandlerThread(Login& login_)
                    :HandlerThread(true), login(login_) {
}


void LoginHandlerThread::run() {
    while (!(login.clientIsConnectedToMatch())) {
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
    if (!login.pixelIsOnAButton(pixel)){
        return;
    } else {
        login.pressButtonThatHasPixel(pixel);
    }

}

