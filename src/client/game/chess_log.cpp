#include "chess_log.h"
#include  "../sdl/game_scene.h"
#include <string>

ChessLog::ChessLog(GameScene &scene) : scene(scene) {}

void
ChessLog::addMessage(std::string message) {
  scene.addLogMessage(message);
}


