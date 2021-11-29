#include "drawable_chat_message.h"

DrawableChatMessage::DrawableChatMessage(Renderer &renderer, Font &font,
                                         const std::string &name,
                                         const std::string &id,
                                         const std::string &time,
                                         const std::string &message) :
    renderer(renderer),
    font(font),
    name(renderer, font, name, 'w'),
    id(renderer, font, "#" + id, 't'),
    time(renderer, font, time, 'd'),
    message(renderer, font, message, 'w') {}

void DrawableChatMessage::render(int x, int y) {
  int x_pos = x, y_pos = y;
  name.render(x_pos, y_pos);
  x_pos += name.getDrawableWidth();
  id.render(x_pos, y_pos);
  x_pos += id.getDrawableWidth();
  DrawableText colon(renderer, font, ": ");
  colon.render(x_pos, y_pos);
  x_pos += colon.getDrawableWidth();
  time.render(x_pos, y_pos);
  y_pos += name.getDrawableHeight();
  x_pos = x;
  message.render(x_pos, y_pos);
  height = y_pos - y;
}

DrawableChatMessage::DrawableChatMessage(DrawableChatMessage &&other) noexcept:
    renderer(other.renderer), font(other.font), name(std::move(other.name)),
    id(std::move(other.id)),
    time(std::move(other.time)), message(std::move(other.message)) {}

int DrawableChatMessage::getDrawableHeight() const {
  return height;
}
