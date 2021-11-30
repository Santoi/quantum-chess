#include "chess_log.h"
#include  "../sdl/scene.h"

ChessLog::ChessLog(Scene &scene) : scene(scene) {}

void
ChessLog::addMessage(std::string message) {
  scene.addLogMessage(message);
}


