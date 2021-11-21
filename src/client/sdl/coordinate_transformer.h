#ifndef QUANTUM_CHESS_PROJ_COORDINATE_TRANSFORMER_H
#define QUANTUM_CHESS_PROJ_COORDINATE_TRANSFORMER_H

#include "pixel_coordinate.h"
#include "../position.h"

class CoordinateTransformer {
public:
  void position2Pixel(const Position &position, PixelCoordinate &pixel,
                      int scale_factor);

  void pixel2Position(const PixelCoordinate &pixel, Position &position,
                      int scale_factor);
};


#endif //QUANTUM_CHESS_PROJ_COORDINATE_TRANSFORMER_H
