#ifndef QUANTUM_CHESS_PROJ_SCENE_H
#define QUANTUM_CHESS_PROJ_SCENE_H

#include "chat/text_sprite_repository.h"
#include "chessman_sprite_repository.h"
#include "../game/drawable_chess.h"
#include "chat/drawable_container.h"
#include "chat/drawable_chat_message.h"


class Window;

class Scene {
private:
  Window &window;
  Font &font;
  Board &chess;
  DrawableContainer<DrawableChatMessage> chat;
  DrawableContainer<DrawableText> log;
  DrawableContainer<DrawableText> error_log;
  DrawableContainer<DrawableText> turn_log;
  DrawableContainer<DrawableText> current_message;
  CoordinateTransformer transformer;
  std::mutex mutex;
  TextSpriteRepository text_repository;


public:
  Scene(Window &window, Board &board, Font &font);

  void render();

  int getChatWidth();

  int getChatHeight();

  int getChessWidth();

  int getChessHeight();

  void addChatMessage(const std::string &nickname, const std::string &id,
                      const std::string &timestamp, const std::string &message);

  void addLogMessage(std::string text);

  void addErrorLogMessage(std::string text);

  void addCurrentMessage(std::string text);

  void addTurnLogMessage(std::string text);

};


#endif //QUANTUM_CHESS_PROJ_SCENE_H
