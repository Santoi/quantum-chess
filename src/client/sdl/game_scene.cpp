#include "game_scene.h"

#include <utility>
#include "window.h"
#include "sprite_repositories/chessman_sprite_repository.h"
#include "drawables/drawable_board.h"


#define MAX_CHAT_MESSAGES 9
#define MAX_LOG_MESSAGES 13
#define MAX_ERROR_LOG_MESSAGES 1
#define MAX_TURN_LOG_MESSAGES 1

#define MIN_CHAT_WIDTH 200
#define MAX_CHAT_WIDTH 400
#define CHAT_WIDTH 300

GameScene::GameScene(Window &window, DrawableBoard &board, Font &font,
                     TextSpriteRepository &text_repository,
                     ButtonSpriteRepository &button_repository)
    : Scene(window), font(font), chess(board),
      chat(MAX_CHAT_MESSAGES),
      log(MAX_LOG_MESSAGES), error_log(
        MAX_ERROR_LOG_MESSAGES), turn_log(MAX_TURN_LOG_MESSAGES),
      current_message(text_repository, button_repository, "CHAT HERE"),
      transformer(), render_help_screen(false),
      mutex(),
      text_repository(text_repository),
      button_repository(button_repository) {}

void
GameScene::addChatMessage(const std::string &nickname, const std::string &id,
                          const std::string &timestamp,
                          const std::string &message) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableChatMessage msg(window.renderer(), font, nickname, id, timestamp,
                          message, text_repository);
  chat.addDrawable(std::move(msg));
}

void GameScene::addLogMessage(std::string text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableText msg(text_repository, text, 'w');
  log.addDrawable(std::move(msg));
}

void GameScene::addErrorLogMessage(std::string text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableText msg(text_repository, text, 'r');
  error_log.addDrawable(std::move(msg));
}

void GameScene::clearErrorLog() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  error_log.clear();
}

void GameScene::addTurnLogMessage(std::string text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableText msg(text_repository, text, 'g');
  turn_log.addDrawable(std::move(msg));
}

void GameScene::addCurrentMessage(const std::string &text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  current_message_text = text;
}

void GameScene::render() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  int width = window.getWidth(), height = window.getHeight();

  chess.render(transformer, width - CHAT_WIDTH, height);

  error_log.render(width - CHAT_WIDTH, 0);
  turn_log.render(width - CHAT_WIDTH, font.size() * 2);
  log.render(width - CHAT_WIDTH, height / 2 - font.size() * 5);
  chat.render(width - CHAT_WIDTH, height - font.size() * 5);
  current_message.setAreaAndPosition(width - CHAT_WIDTH,
                                     height - font.size() * 2, CHAT_WIDTH,
                                     font.size() * 2);
  current_message.render(current_message_text);
}

int GameScene::getChatWidth() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return CHAT_WIDTH;
}

int GameScene::getChatHeight() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return window.getHeight();
}

int GameScene::getChessWidth() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return window.getWidth() - CHAT_WIDTH;
}

int GameScene::getChessHeight() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return window.getHeight();
}

bool GameScene::wasChatClicked(PixelCoordinate &pixel) {
  return current_message.pixelIsOnTextEntry(pixel);
}

void GameScene::disableChat() {
  // hack, chat is never there
  PixelCoordinate p(0, 0);
  current_message.pixelIsOnTextEntry(p);
}

void GameScene::stopRenderingHelpScreen() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  render_help_screen = false;
}

void GameScene::startRenderingHelpScreen() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  render_help_screen = true;
}
