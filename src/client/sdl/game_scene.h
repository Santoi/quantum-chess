#ifndef QUANTUM_CHESS_PROJ_GAME_SCENE_H
#define QUANTUM_CHESS_PROJ_GAME_SCENE_H

#include "sprite_repositories/text_sprite_repository.h"
#include "sprite_repositories/chessman_sprite_repository.h"
#include "drawables/drawable_board.h"
#include "drawables/drawable_container.h"
#include "drawables/drawable_chat_message.h"
#include "scene.h"
#include "sprite_repositories/button_sprite_repository.h"
#include "drawables/drawable_text_entry_button.h"


class Window;

class GameScene : public Scene {
private:
  Font &font;
  DrawableBoard &chess;
  DrawableContainer<DrawableChatMessage> chat;
  DrawableContainer<DrawableText> log;
  DrawableContainer<DrawableText> error_log;
  DrawableContainer<DrawableText> turn_log;
  DrawableTextEntryButton current_message;
  CoordinateTransformer transformer;
  std::mutex mutex;
  TextSpriteRepository &text_repository;
  ButtonSpriteRepository &button_repository;
  std::string current_message_text;

public:
  GameScene(Window &window, DrawableBoard &board, Font &font,
            TextSpriteRepository &text_repository,
            ButtonSpriteRepository &button_repository);

  // Render the whole in-game scene
  void render() override;

  int getChatWidth();

  int getChessWidth();

  int getChessHeight();

  // Create and add a chat message to the chat
  void addChatMessage(const std::string &nickname, const std::string &id,
                      const std::string &timestamp, const std::string &message);

  // Create and add a log message to the chat
  void addLogMessage(std::string text);

  // Create and add an error log message to the chat
  void addErrorLogMessage(std::string text);

  // Create and add current message to the text entry box
  void addCurrentMessage(const std::string &text);

  // Create and add a "whose turn it is" message to the chat
  void addTurnLogMessage(std::string text);

  // Erase all error log messages
  void clearErrorLog();

  bool wasChatClicked(PixelCoordinate &pixel);

  void disableChat();
};


#endif //QUANTUM_CHESS_PROJ_GAME_SCENE_H
