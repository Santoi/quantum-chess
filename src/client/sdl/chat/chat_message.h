#ifndef QUANTUM_CHESS_PROJ_CHAT_MESSAGE_H
#define QUANTUM_CHESS_PROJ_CHAT_MESSAGE_H

#include "../renderer.h"
#include "font.h"
#include "drawable_text.h"
#include <string>

class ChatMessage {
  Renderer &renderer;
  Font &font;
  DrawableText name;
  DrawableText id;
  DrawableText time;
  DrawableText message;

public:
  ChatMessage(Renderer &renderer, Font &font,
              const std::string &name, const std::string &id,
              const std::string &time, const std::string &message);

  void render(int x, int y);
};


#endif //QUANTUM_CHESS_PROJ_CHAT_MESSAGE_H
