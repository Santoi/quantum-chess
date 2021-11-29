#include "scene.h"
#include "window.h"

#define MAX_CHAT_MESSAGES 3
#define MAX_LOG_MESSAGES 3
#define MAX_ERROR_LOG_MESSAGES 1

#define CHAT_WIDTH 50

Scene::Scene(Window &window, Board &board) : window(window), chess(board),
                                             chat(MAX_CHAT_MESSAGES),
                                             log(MAX_LOG_MESSAGES), error_log(
        MAX_ERROR_LOG_MESSAGES) {}

void Scene::render() {
  int width = window.getWidth(), height = window.getHeight();
  float total_messages =
      MAX_CHAT_MESSAGES + MAX_LOG_MESSAGES + MAX_ERROR_LOG_MESSAGES;
  chess.render(transformer, window.getWidth() - CHAT_WIDTH, window.getHeight());
  error_log.render(width - CHAT_WIDTH, 0);
  log.render(width - CHAT_WIDTH,
             height * (MAX_ERROR_LOG_MESSAGES / total_messages));
  chat.render(width - CHAT_WIDTH,
              height *
              ((MAX_ERROR_LOG_MESSAGES + MAX_LOG_MESSAGES) / total_messages));
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
