#ifndef QUANTUM_CHESS_PROJ_RENDERER_H
#define QUANTUM_CHESS_PROJ_RENDERER_H

#include "sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <algorithm>

class Sprite;
class Scene;

class Renderer {
private:
  SDL2pp::Renderer renderer_;

public:
  explicit Renderer(SDL2pp::Window &window);
  SDL2pp::Renderer& renderer();

  void render(Scene &scene);

  // SDL2pp wrappers
  // Render the sprite starting at (x, y)
  void copy(Sprite &sprite, int x, int y);
  void copy(Sprite &sprite, int x_src, int y_src, int x_dst, int y_dst,
            int width, int height);
  int getMinDimension();
};


#endif //QUANTUM_CHESS_PROJ_RENDERER_H
