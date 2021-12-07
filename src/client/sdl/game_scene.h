#ifndef QUANTUM_CHESS_PROJ_GAME_SCENE_H
#define QUANTUM_CHESS_PROJ_GAME_SCENE_H

#include "sprite_repositories/text_sprite_repository.h"
#include "sprite_repositories/chessman_sprite_repository.h"
#include "../game/drawable_chess.h"
#include "chat/drawable_container.h"
#include "chat/drawable_chat_message.h"
#include "scene.h"
#include "sprite_repositories/button_sprite_repository.h"


class Window;

class GameScene : public Scene {
private:
  Font &font;
  DrawableBoard &chess;
  DrawableContainer<DrawableChatMessage> chat;
  DrawableContainer<DrawableText> log;
  DrawableContainer<DrawableText> error_log;
  DrawableContainer<DrawableText> turn_log;
  DrawableContainer<DrawableText> current_message;
  CoordinateTransformer transformer;
  std::mutex mutex;
  TextSpriteRepository &text_repository;
  ButtonSpriteRepository &button_repository;

public:
  GameScene(Window &window, DrawableBoard &board, Font &font,
            TextSpriteRepository &text_repository,
            ButtonSpriteRepository &button_repository);

  void render() override;

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

  void clearErrorLog();
};


#endif //QUANTUM_CHESS_PROJ_GAME_SCENE_H
