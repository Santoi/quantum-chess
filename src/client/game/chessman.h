#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H

#include "../sdl/renderer.h"
#include "../sdl/texture_sprite.h"
#include <map>
#include <string>

class Renderer;

class Chessman {
private:
  Renderer &renderer;
  TextureSprite sprite_;
  TextureSprite fill;
  std::map<std::string, std::pair<std::string, std::string>> image;
  float probability;

public:
  Chessman(Renderer &renderer, const std::string &chessman, int probability_);
  Chessman(Chessman &&other) noexcept;
  Chessman(const Chessman &other) = delete;
  Chessman& operator=(Chessman &&other) noexcept;
  void render(int x, int y);
  ~Chessman();
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
