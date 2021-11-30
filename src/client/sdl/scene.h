#ifndef QUANTUM_CHESS_PROJ_SCENE_H
#define QUANTUM_CHESS_PROJ_SCENE_H

#include "../game/drawable_chess.h"
#include "chat/drawable_container.h"
#include "chat/drawable_chat_message.h"

class Window;

class Scene {
private:
  Window &window;
  Font &font;
  DrawableChess chess;
  DrawableContainer<DrawableChatMessage> chat;
  DrawableContainer<DrawableText> log;
  DrawableContainer<DrawableText> error_log;
  DrawableContainer<DrawableText> current_message;
  CoordinateTransformer transformer;

public:
  Scene(Window &window, Board &board, Font &font);

  void render();

  int getChatWidth() const;

  int getChatHeight() const;

  int getChessWidth() const;

  int getChessHeight() const;
};


#endif //QUANTUM_CHESS_PROJ_SCENE_H
