#ifndef QUANTUM_CHESS_PROJ_GAME_SCENE_H
#define QUANTUM_CHESS_PROJ_GAME_SCENE_H

#include "sprite_repositories/text_sprite_repository.h"
#include "sprite_repositories/chessman_sprite_repository.h"
#include "drawables/drawable_chess.h"
#include "drawables/drawable_container.h"
#include "drawables/drawable_chat_message.h"
#include "scene.h"
#include "screen_handler.h"
#include "sprite_repositories/button_sprite_repository.h"
#include "drawables/drawable_text_entry_button.h"


class Window;

class ScreenHandler;

class GameScene : public Scene {
private:
    Font &font;
    DrawableBoard &chess;
    DrawableContainer<DrawableChatMessage> chat;
    DrawableContainer<DrawableText> log;
    DrawableContainer<DrawableText> error_log;
    DrawableContainer<DrawableText> turn_log;
    DrawableTextEntryButton current_message;
    CoordinateTransformer &transformer;
    ScreenHandler &screen_handler;
    std::mutex mutex;
    TextSpriteRepository &text_repository;
    ButtonSpriteRepository &button_repository;
    TextureSprite* help_sprite;
    TextureSprite* leave_sprite;
    TextureSprite* surrender_leave_sprite;
    std::string current_message_text;

public:
    GameScene(Window &window, DrawableBoard &board, Font &font,
              ScreenHandler &screen_handler,
              TextSpriteRepository &text_repository,
              ButtonSpriteRepository &button_repository,
              CoordinateTransformer &transformer_);

    void render() override;

    int getChatWidth();

    int getChatHeight();

    int getChessWidth();

    int getChessHeight();

    void addChatMessage(const std::string &nickname, const std::string &id,
                        const std::string &timestamp, const std::string &message);

    void addLogMessage(std::string text);

    void addErrorLogMessage(std::string text);

    void addCurrentMessage(const std::string &text);

    void addTurnLogMessage(std::string text);

    void clearErrorLog();

    bool wasChatClicked(PixelCoordinate &pixel);

    void disableChat();

    void renderHelpScreen();

    void renderLeaveMatchScreenForSpectators();

    void renderLeaveMatchScreenForPlayers();

    void renderGame();
};


#endif //QUANTUM_CHESS_PROJ_GAME_SCENE_H
