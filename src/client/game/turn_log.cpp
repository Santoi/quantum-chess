#include "turn_log.h"
#include  "../sdl/scene.h"

TurnLog::TurnLog(Scene &scene) : scene(scene) {}

void
TurnLog::changeTurn(bool white) {
  std::string message = white ? "White" : "Black";
  scene.addTurnLogMessage(message + " plays");
}


