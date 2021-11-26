#include "lobby_handler_thread.h"

LobbyHandlerThread::LobbyHandlerThread(Lobby& lobby_)
                    :active_lobby(true), lobby(lobby_) {
}


void LobbyHandlerThread::run() {
    while (this->active_lobby) {
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
}

void LobbyHandlerThread::setLobbyInactive() {
    active_lobby = false;
}

void LobbyHandlerThread::handleMouseButtonLeft(SDL_MouseButtonEvent &mouse) {
    PixelCoordinate pixel(mouse.x, mouse.y);
    if (!lobby.pixelIsOnBottom(pixel))
        return;
}

