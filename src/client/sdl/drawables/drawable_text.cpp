#include "drawable_text.h"
#include "../renderer.h"
#include <string>
#include <iostream>
#include <utility>
#include "../sprite_repositories/text_sprite_repository.h"

#define SCALE_FACTOR 10
#define RENDER_HEIGHT_SCALE_FACTOR 28
#define HEIGHT_SCALE_FACTOR 14

DrawableText::DrawableText(TextSpriteRepository &text_sprite_repository_,
                           std::string text, char color) :
    text_sprite_repository(text_sprite_repository_),
    text(std::move(text)),
    color(color) {}

DrawableText::DrawableText(DrawableText &&other) noexcept:
    text_sprite_repository(other.text_sprite_repository),
    text(std::move(other.text)),
    color(other.color) {
}

void DrawableText::render(size_t x, size_t y) {
  if (!text.empty()) {
    for (auto c: text) {
      Sprite &sprite = text_sprite_repository.getChar(c, color);
      sprite.render(x, y);
      x += sprite.width();
    }
  }
}

size_t DrawableText::getDrawableWidth() const {
  return text.size() * text_sprite_repository.getSpriteSize();
}

size_t DrawableText::getDrawableHeight() const {
  return text_sprite_repository.getSpriteSize();
}

void DrawableText::setText(const std::string &text_) {
  text = text_;
}

void DrawableText::setColor(char color_) {
  color = color_;
}
