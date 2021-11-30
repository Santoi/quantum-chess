#include "scene.h"
#include "window.h"

#define MAX_CHAT_MESSAGES 5
#define MAX_LOG_MESSAGES 7
#define MAX_ERROR_LOG_MESSAGES 1

#define MIN_CHAT_WIDTH 200
#define MAX_CHAT_WIDTH 400
#define CHAT_WIDTH 200

Scene::Scene(Window &window, Board &board, Font &font)
    : window(window), font(font), chess(board),
      chat(MAX_CHAT_MESSAGES),
      log(MAX_LOG_MESSAGES), error_log(
        MAX_ERROR_LOG_MESSAGES), current_message(1) {
  DrawableChatMessage msg1(window.renderer(), font, "santi", "0", "00:01",
                           "hola");
  chat.addDrawable(std::move(msg1));
  DrawableChatMessage msg2(window.renderer(), font, "mati", "1", "00:01",
                           "hola santi");
  chat.addDrawable(std::move(msg2));
  DrawableChatMessage msg3(window.renderer(), font, "santi", "0", "00:02",
                           "no anda ni de onda esto");
  chat.addDrawable(std::move(msg3));
  DrawableText log_msg(window.renderer(), font, "B4 moved to E3");
  DrawableText log_msg2(window.renderer(), font, "B4 moved to E4");
  log.addDrawable(std::move(log_msg));
  log.addDrawable(std::move(log_msg2));
  DrawableText error_log_msg(window.renderer(), font, "Invalid move", 'r');
  error_log.addDrawable(std::move(error_log_msg));
}

void Scene::render() {
  int width = window.getWidth(), height = window.getHeight();
  float total_messages = MAX_CHAT_MESSAGES +
                         MAX_LOG_MESSAGES +
                         MAX_ERROR_LOG_MESSAGES +
                         1; // +1 bc of current message

  chess.render(transformer, width - CHAT_WIDTH, height);

  error_log.render(width - CHAT_WIDTH, 0);
  log.render(width - CHAT_WIDTH,
             height *
             ((MAX_ERROR_LOG_MESSAGES + MAX_LOG_MESSAGES) / total_messages));
  chat.render(width - CHAT_WIDTH,
              height *
              ((MAX_ERROR_LOG_MESSAGES + MAX_LOG_MESSAGES + MAX_CHAT_MESSAGES) /
               total_messages));
  current_message.render(width - CHAT_WIDTH,
                         height * (total_messages - 1) / total_messages);
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
