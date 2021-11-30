#include "error_log.h"
#include  "../sdl/scene.h"

ErrorLog::ErrorLog(Scene &scene) : scene(scene) {}

void
ErrorLog::addMessage(std::string message) {
  scene.addErrorLogMessage(message);
}


