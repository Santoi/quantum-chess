#ifndef QUANTUM_CHESS_PROJ_SPRITE_H
#define QUANTUM_CHESS_PROJ_SPRITE_H

#include <SDL2pp/SDL2pp.hh>
#include <string>

#define DEFAULT_SPRITE "img/default.png"

class Sprite {
private:
  SDL2pp::Renderer &renderer;
  SDL2pp::Texture sprite;

public:
  explicit Sprite(SDL2pp::Renderer &renderer,
                                const std::string &file_name = DEFAULT_SPRITE);
  Sprite(Sprite &&other) = default;
  Sprite& operator=(Sprite &other);

  void render();

  // Render the current sprite from (x, y) to (x + width, y + height)
  void render(int x, int y, int width, int height);

  void loadImage(const std::string &file_name);

  ~Sprite();
};


#endif //QUANTUM_CHESS_PROJ_SPRITE_H
