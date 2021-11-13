#ifndef QUANTUM_CHESS_PROJ_UTILITY_H
#define QUANTUM_CHESS_PROJ_UTILITY_H

#include "position.h"
#include <SDL2pp/SDL2pp.hh>

class Utility {
public:
  static void getTilePosition(const SDL2pp::Renderer &renderer,
                              Position &position, int x, int y);
};


#endif //QUANTUM_CHESS_PROJ_UTILITY_H
