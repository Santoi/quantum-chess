#ifndef QUANTUM_CHESS_PROJ_SPRITE_H
#define QUANTUM_CHESS_PROJ_SPRITE_H

#include "renderer.h"
#include <SDL2pp/SDL2pp.hh>

class Renderer;

class Sprite {
protected:
  Renderer &renderer;
  SDL2pp::Texture sprite_;
  int width_, height_;

public:
  Sprite(Renderer &renderer, const std::string &file_name,
         int width = 0,
         int height = 0);

  Sprite(Renderer &renderer, const SDL2pp::Surface &surface,
         int width = 0,
         int height = 0);

  int width() const;

  int height() const;

  SDL2pp::Texture &sprite();
};


#endif //QUANTUM_CHESS_PROJ_SPRITE_H
