#ifndef QUANTUM_CHESS_PROJ_RENDERER_H
#define QUANTUM_CHESS_PROJ_RENDERER_H

#include <SDL2pp/SDL2pp.hh>
#include <algorithm>
//#include "scene.h"

class Sprite;

class Scene;

class Renderer {
private:
  SDL2pp::Renderer renderer_;

public:
  explicit Renderer(SDL2pp::Window &window);

  SDL2pp::Renderer &renderer();

  void render(Scene &scene);

  // SDL2pp wrappers
  // Render the sprite starting at (x, y)
  void copy(Sprite &sprite, size_t x, size_t y);

  void
  copy(Sprite &sprite, size_t x_src, size_t y_src, size_t x_dst, size_t y_dst,
       size_t width, size_t height);

  size_t getMinDimension() const;

  size_t getWidth() const;

  size_t getHeight() const;
};


#endif //QUANTUM_CHESS_PROJ_RENDERER_H
