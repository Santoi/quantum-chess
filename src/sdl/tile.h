#ifndef QUANTUM_CHESS_PROJ_TILE_H
#define QUANTUM_CHESS_PROJ_TILE_H

#include "sprite.h"
#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <string>

class Tile {
private:
  SDL2pp::Renderer &renderer;
  Sprite sprite;
  std::map<int, std::string> images;

  typedef enum {
    DEFAULT, MOVE, ENTANGLE, SPLIT
  } SquareType;

public:
  Tile(SDL2pp::Renderer &renderer, bool black);
  Tile(Tile &&other) noexcept;
//  Tile& operator=(Tile &other);
  void render(int x, int y);
  void loadDefault();
  void loadMove();
  void loadEntagle();
  void loadSplit();
};


#endif //QUANTUM_CHESS_PROJ_TILE_H
