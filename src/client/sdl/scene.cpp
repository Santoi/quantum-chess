#include "scene.h"

#include <utility>
#include "window.h"

#define MAX_CHAT_MESSAGES 5
#define MAX_LOG_MESSAGES 7
#define MAX_ERROR_LOG_MESSAGES 1

#define MIN_CHAT_WIDTH 200
#define MAX_CHAT_WIDTH 400
#define CHAT_WIDTH 250

Scene::Scene(Window &window, Board &board, Font &font)
    : window(window), font(font), chess(board),
      chat(MAX_CHAT_MESSAGES),
      log(MAX_LOG_MESSAGES), error_log(
        MAX_ERROR_LOG_MESSAGES), current_message(1), mutex() {}

void Scene::addChatMessage(const std::string &nickname, const std::string &id,
                           const std::string &timestamp,
                           const std::string &message) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableChatMessage msg(window.renderer(), font, nickname, id, timestamp,
                          message);
  chat.addDrawable(std::move(msg));
}

void Scene::addLogMessage(std::string text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableText msg(window.renderer(), font, std::move(text));
  log.addDrawable(std::move(msg));
}

void Scene::addErrorLogMessage(std::string text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableText msg(window.renderer(), font, std::move(text));
  error_log.addDrawable(std::move(msg));
}

void Scene::addCurrentMessage(std::string text) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  DrawableText msg(window.renderer(), font, std::move(text));
  current_message.addDrawable(std::move(msg));
}

void Scene::render() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  int width = window.getWidth(), height = window.getHeight();

  chess.render(transformer, width - CHAT_WIDTH, height);

  error_log.render(width - CHAT_WIDTH, 0);
  log.render(width - CHAT_WIDTH, height / 2 - font.size() * 5);
  chat.render(width - CHAT_WIDTH, height - font.size() * 5);
  current_message.render(width - CHAT_WIDTH, height - font.size());
}

int Scene::getChatWidth() const {
  return CHAT_WIDTH;
}

int Scene::getChatHeight() const {
  return window.getHeight();
}

int Scene::getChessWidth() const {
  return window.getWidth() - CHAT_WIDTH;
}

int Scene::getChessHeight() const {
  return window.getHeight();
}
