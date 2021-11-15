#ifndef QUANTUM_CHESS_PROJ_TILE_H
#define QUANTUM_CHESS_PROJ_TILE_H

#include "sprite.h"
#include "renderer.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>

class Tile {
private:
  Renderer &renderer;
  Sprite sprite_;
  std::map<int, std::string> images;

  typedef enum {
    DEFAULT, MOVE, ENTANGLE, SPLIT
  } SquareType;

public:
  Tile(Renderer &renderer, bool black);
  Tile(Tile &&other) noexcept;
  Tile(const Tile &other) = delete;
  Tile& operator=(Tile &&other) noexcept;
  void render(int x, int y);
  void loadDefault();
  void loadMove();
  void loadEntagle();
  void loadSplit();
};


#endif //QUANTUM_CHESS_PROJ_TILE_H
