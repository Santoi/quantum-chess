#ifndef QUANTUM_CHESS_PROJ_RENDERER_H
#define QUANTUM_CHESS_PROJ_RENDERER_H

#include "window.h"
#include "sprite.h"
#include <SDL2pp/SDL2pp.hh>

class Sprite;
class Scene;

class Renderer {
private:
  SDL2pp::Renderer renderer_;

public:
  explicit Renderer(Window &window);
  SDL2pp::Renderer& renderer();

  void render(Scene &scene);

  // SDL2pp wrappers
  // Render the sprite starting at (x, y)
  void copy(Sprite &sprite, int x, int y);
  void clear();
  int getMinDimension();
};


#endif //QUANTUM_CHESS_PROJ_RENDERER_H
