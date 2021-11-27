#include "drawable_text.h"
#include "../renderer.h"
#include "text_sprite.h"
#include <string>
#include <iostream>
#include <utility>

#define SCALE_FACTOR 30
#define HEIGHT_SCALE_FACTOR 32

DrawableText::DrawableText(Renderer &renderer_, Font &font_, std::string text,
                           char color) :
    renderer(renderer_),
    sprite(renderer_,
           font_, " "),
    font(font_),
    text(std::move(text)),
    color(color) {}

DrawableText::DrawableText(DrawableText &&other) noexcept:
    renderer(
        other.renderer),
    sprite(std::move(
        other.sprite)),
    font(other.font),
    text(std::move(
        other.text)),
    color(other.color) {}

void DrawableText::render(int x, int y) {
  if (!text.empty())
    sprite.render(text, x, y,
                  text.size() * renderer.getMinDimension() / SCALE_FACTOR,
                  renderer.getMinDimension() / SCALE_FACTOR, color);
}

size_t DrawableText::length() const {
  return text.size();
}

int DrawableText::getTextOutputWidth() const {
  return text.size() * renderer.getWidth() / SCALE_FACTOR;
}

int DrawableText::getTextOutputHeight() const {
  return renderer.getWidth() / HEIGHT_SCALE_FACTOR;
}
