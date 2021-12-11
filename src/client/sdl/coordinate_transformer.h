#ifndef QUANTUM_CHESS_PROJ_COORDINATE_TRANSFORMER_H
#define QUANTUM_CHESS_PROJ_COORDINATE_TRANSFORMER_H

#include "pixel_coordinate.h"
#include "../game/position.h"

class CoordinateTransformer {
public:
  void position2Pixel(const Position &position,
                      PixelCoordinate &pixel, int width,
                      int height);

  void pixel2Position(const PixelCoordinate &pixel,
                      Position &position, int width,
                      int height);
};


#endif //QUANTUM_CHESS_PROJ_COORDINATE_TRANSFORMER_H
