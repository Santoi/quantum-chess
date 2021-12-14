#ifndef QUANTUM_CHESS_SRC_SCREEN_HANDLER_H
#define QUANTUM_CHESS_SRC_SCREEN_HANDLER_H

#include "game_scene.h"
#include "../game/game.h"
#include <mutex>

class GameScene;

class ScreenHandler {
private:
    bool render_help_screen;
    bool render_leave_match_screen;
    bool client_is_spectator;
    std::mutex mutex;

public:
    ScreenHandler() = delete;

    explicit ScreenHandler(bool client_is_spectator_);

    void renderCurrentState(GameScene &game_scene);

    void toggleHelpScreen();

    void activateLeaveScreen();

    void deactivateLeaveScreen();

    void switchOpenStatusIfLeaveMatchScreenIsRendering(std::atomic<bool>& open);

    void surrenderMatchIfLeaveMatchScreenIsRendering(Game &game);

    bool renderingGame();
};


#endif //QUANTUM_CHESS_SRC_SCREEN_HANDLER_H
