#include "screen_handler.h"

ScreenHandler::ScreenHandler(bool client_is_spectator_)
              :render_help_screen(false),
               render_leave_match_screen(false),
               client_is_spectator(client_is_spectator_) {
}

void ScreenHandler::renderCurrentState(GameScene &game_scene) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (!render_help_screen && !render_leave_match_screen) { //most likely case
    game_scene.renderGame();
  } else if (render_help_screen) {
    game_scene.renderHelpScreen();
  } else {
    if (client_is_spectator)
      game_scene.renderLeaveMatchScreenForSpectators();
    else
      game_scene.renderLeaveMatchScreenForPlayers();
  }
}

void ScreenHandler::toggleHelpScreen() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (render_leave_match_screen)
    return;
  render_help_screen = !render_help_screen;
}


void ScreenHandler::toggleLeaveScreen() {
  if (render_help_screen)
    return;
  render_leave_match_screen = !render_leave_match_screen;
}

void ScreenHandler::activateLeaveScreen() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (render_help_screen)
    return;
  render_leave_match_screen = true;
}

void ScreenHandler::deactivateLeaveScreen() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  render_leave_match_screen = false;
}

void ScreenHandler::switchOpenStatusIfLeaveMatchScreenIsRendering(
                                                  std::atomic<bool>& open) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (render_leave_match_screen)
    open = false;
  render_leave_match_screen = false;
}

void ScreenHandler::surrenderMatchIfLeaveMatchScreenIsRendering(Game &game) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  if (render_leave_match_screen)
    game.surrender();
  toggleLeaveScreen();
}

bool ScreenHandler::renderingGame() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return !(render_leave_match_screen || render_help_screen);
}

void ScreenHandler::renderGameScreen() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  render_leave_match_screen = false;
  render_help_screen = false;
}
