#include "turn_log.h"
#include  "../sdl/game_scene.h"
#include <string>

TurnLog::TurnLog(GameScene &scene) : scene(scene) {}

void
TurnLog::changeTurn(bool white, ClientData::Role role) {
  std::string message = white ? "White" : "Black";
  message += " plays - You ";
  switch (role) {
    case ClientData::ROLE_WHITE:
      message += "white";
      break;
    case ClientData::ROLE_BLACK:
      message += "black";
      break;
    case ClientData::ROLE_SPECTATOR:
      message += "spectator";
      break;
  }
  scene.addTurnLogMessage(message);
}


