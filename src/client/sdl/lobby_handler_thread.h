#ifndef QUANTUM_CHESS_PROJ_LOBBY_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_LOBBY_HANDLER_THREAD_H

#include "../../common/src/thread.h"
#include "lobby.h"
#include "pixel_coordinate.h"
#include <SDL2/SDL.h>
#include <atomic>

class LobbyHandlerThread : public Thread {
private:
    std::atomic<bool> active_lobby;
    PixelCoordinate last_click;
    SDL_Event event;
    Lobby& lobby;
    void handleMouseButtonLeft(SDL_MouseButtonEvent &mouse);

public:
    LobbyHandlerThread() = delete;

    LobbyHandlerThread(Lobby& lobby_);

    // Event loop
    void run() override;

    void setLobbyInactive();
};

#endif //QUANTUM_CHESS_PROJ_LOBBY_HANDLER_THREAD_H
