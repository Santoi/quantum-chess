#ifndef QUANTUM_CHESS_PROJ_SPRITE_H
#define QUANTUM_CHESS_PROJ_SPRITE_H

#include "renderer.h"
#include <SDL2pp/SDL2pp.hh>

class Renderer;

class Sprite {
protected:
  Renderer &renderer;
  SDL2pp::Texture sprite_;
  size_t width_, height_;

public:
  Sprite(Renderer &renderer, const std::string &file_name,
         size_t width = 0,
         size_t height = 0);

  Sprite(Renderer &renderer, const SDL2pp::Surface &surface,
         size_t width = 0,
         size_t height = 0);

  size_t width() const;

  size_t height() const;

  SDL2pp::Texture &sprite();

  // Render sprite with current width and height
  virtual void render(size_t x, size_t y);

  // Render sprite with a new width and height
  virtual void render(size_t x, size_t y, size_t width, size_t height);
};


#endif //QUANTUM_CHESS_PROJ_SPRITE_H
