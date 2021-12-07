#include "turn_log.h"
#include  "../sdl/game_scene.h"

TurnLog::TurnLog(GameScene &scene) : scene(scene) {}

void
TurnLog::changeTurn(bool white) {
  std::string message = white ? "White" : "Black";
  scene.addTurnLogMessage(message + " plays");
}


