#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_CHAT_MESSAGE_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_CHAT_MESSAGE_H

#include "drawable_text.h"
#include "font.h"
#include <string>

class Renderer;

class DrawableChatMessage {
  Renderer &renderer;
  Font &font;
  DrawableText name;
  DrawableText id;
  DrawableText time;
  DrawableText message;
  int height = 0;

public:
  DrawableChatMessage(Renderer &renderer, Font &font,
                      const std::string &name, const std::string &id,
                      const std::string &time, const std::string &message);

  DrawableChatMessage(DrawableChatMessage &&other) noexcept;

  void render(int x, int y);

  int getDrawableHeight() const;
};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_CHAT_MESSAGE_H
