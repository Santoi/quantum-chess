#ifndef QUANTUM_CHESS_PROJ_SPRITE_H
#define QUANTUM_CHESS_PROJ_SPRITE_H

#include <SDL2pp/SDL2pp.hh>
#include <string>

class Sprite {
private:
  SDL2pp::Renderer &renderer;
  SDL2pp::Texture sprite;

public:
  Sprite(SDL2pp::Renderer &renderer, const std::string &file_name);
  Sprite(SDL2pp::Renderer &renderer, const std::string &file_name,
                                                         int width, int height);

  void render();

  // Render the current sprite from (x, y) to (width, height)
  void render(int x, int y, int width, int height);

  void loadImage(const std::string &file_name);

  ~Sprite();
};


#endif //QUANTUM_CHESS_PROJ_SPRITE_H
