#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_CHAT_MESSAGE_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_CHAT_MESSAGE_H

#include "drawable_text.h"
#include "../font.h"
#include <string>

class Renderer;

class DrawableChatMessage {
  Renderer &renderer;
  Font &font;
  DrawableText name;
  DrawableText id;
  DrawableText time;
  DrawableText message;
  TextSpriteRepository &repository;
  int height = 0;


public:
  DrawableChatMessage(Renderer &renderer, Font &font,
                      const std::string &name,
                      const std::string &id,
                      const std::string &time,
                      const std::string &message,
                      TextSpriteRepository &repository);

  // TODO MATI: constructor con Chat::StructChat

  DrawableChatMessage(DrawableChatMessage &&other) noexcept;

  // Render a chat message with sender's nickname, ID and timestamps
  void render(int x, int y);

  int getDrawableHeight() const;
};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_CHAT_MESSAGE_H
