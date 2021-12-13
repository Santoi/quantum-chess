#ifndef QUANTUM_CHESS_PROJ_COORDINATE_TRANSFORMER_H
#define QUANTUM_CHESS_PROJ_COORDINATE_TRANSFORMER_H

#include <atomic>
#include "pixel_coordinate.h"
#include "../game/position.h"

class CoordinateTransformer {
  std::atomic<bool> flipped;

public:
  CoordinateTransformer();

  explicit CoordinateTransformer(bool flipped_);

  void position2Pixel(const Position &position,
                      PixelCoordinate &pixel, int width,
                      int height);

  void pixel2Position(const PixelCoordinate &pixel,
                      Position &position, int width,
                      int height);

  void flip();
};


#endif //QUANTUM_CHESS_PROJ_COORDINATE_TRANSFORMER_H
