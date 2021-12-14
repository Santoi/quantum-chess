#include "error_log.h"
#include  "../sdl/game_scene.h"
#include <string>

ErrorLog::ErrorLog(GameScene &scene) : scene(scene) {}

void
ErrorLog::addMessage(std::string message) {
  scene.addErrorLogMessage(message);
}

void
ErrorLog::clear() {
  scene.clearErrorLog();
}


