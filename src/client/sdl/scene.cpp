#include "scene.h"

#include <utility>
#include "window.h"
#include "../sdl/chessman_sprite_repository.h"
#include "../game/board.h"


#define MAX_CHAT_MESSAGES 9
#define MAX_LOG_MESSAGES 13
#define MAX_ERROR_LOG_MESSAGES 1
#define MAX_TURN_LOG_MESSAGES 1

#define MIN_CHAT_WIDTH 200
#define MAX_CHAT_WIDTH 400
#define CHAT_WIDTH 250

Scene::Scene(Window &window, Board &board, Font &font)
        : window(window), font(font), chess(board),
          chat(MAX_CHAT_MESSAGES),
          log(MAX_LOG_MESSAGES), error_log(
                MAX_ERROR_LOG_MESSAGES), turn_log(MAX_TURN_LOG_MESSAGES),
          current_message(1), mutex(),
          text_repository(window.renderer(), font) {}

void Scene::addChatMessage(const std::string &nickname, const std::string &id,
                           const std::string &timestamp,
                           const std::string &message) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableChatMessage msg(window.renderer(), font, nickname, id, timestamp,
                          message, text_repository);
  chat.addDrawable(std::move(msg));
}

void Scene::addLogMessage(std::string text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableText msg(text_repository, text, 'w');
  log.addDrawable(std::move(msg));
}

void Scene::addErrorLogMessage(std::string text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableText msg(text_repository, text, 'r');
  error_log.addDrawable(std::move(msg));
}

void Scene::addTurnLogMessage(std::string text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableText msg(text_repository, text, 'g');
  turn_log.addDrawable(std::move(msg));
}

void Scene::addCurrentMessage(std::string text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableText msg(text_repository, text, 'w');
  current_message.addDrawable(std::move(msg));
}

void Scene::render() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  int width = window.getWidth(), height = window.getHeight();

  chess.render(transformer, width - CHAT_WIDTH, height);

  error_log.render(width - CHAT_WIDTH, 0);
  turn_log.render(width - CHAT_WIDTH, font.size() * 2);
  log.render(width - CHAT_WIDTH, height / 2 - font.size() * 5);
  chat.render(width - CHAT_WIDTH, height - font.size() * 5);
  current_message.render(width - CHAT_WIDTH, height - font.size());
}

int Scene::getChatWidth() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return CHAT_WIDTH;
}

int Scene::getChatHeight() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return window.getHeight();
}

int Scene::getChessWidth() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return window.getWidth() - CHAT_WIDTH;
}

int Scene::getChessHeight() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return window.getHeight();
}
