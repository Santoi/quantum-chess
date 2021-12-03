#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_H

#include "font.h"
#include "../sprite_repositories/text_sprite_repository.h"
#include <string>

class Renderer;

class TextSpriteRepository;

class DrawableText {
  TextSpriteRepository &text_sprite_repository;
  std::string text;
  char color;


public:
  DrawableText(TextSpriteRepository &text_sprite_repository_,
               std::string text, char color = 'w');

  DrawableText(DrawableText &&other) noexcept;

  DrawableText(const DrawableText &other) = delete;

  size_t length() const;

  int getDrawableWidth() const;

  int getDrawableHeight() const;

  void render(int x, int y);

  void setText(const std::string &text_);

  void setColor(char color_);
};


#endif //QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_H
