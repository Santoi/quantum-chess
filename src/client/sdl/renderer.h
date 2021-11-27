#ifndef QUANTUM_CHESS_PROJ_RENDERER_H
#define QUANTUM_CHESS_PROJ_RENDERER_H

#include "window.h"
#include "texture_sprite.h"
#include "chat/text_sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <algorithm>

class TextureSprite;

class TextSprite;

class Scene;

class Renderer {
private:
  SDL2pp::Renderer renderer_;

public:
  explicit Renderer(Window &window);

  SDL2pp::Renderer &renderer();

  void render(Scene &scene);

  // SDL2pp wrappers
  // Render the sprite starting at (x, y)
  void copy(TextureSprite &sprite, int x, int y);

  void copy(TextureSprite &sprite, int x_src, int y_src, int x_dst, int y_dst,
            int width, int height);

  void copy(TextSprite &sprite, int x, int y);

  int getMinDimension() const;

  int getWidth() const;

  int getHeight() const;
};


#endif //QUANTUM_CHESS_PROJ_RENDERER_H
