#include "coordinate_transformer.h"

void CoordinateTransformer::pixel2Position(const PixelCoordinate &pixel,
                                           Position &position,
                                           int scale_factor) {
  int x = pixel.x(), y = pixel.y();
  x *= 10;
  y *= 10;
  x /= scale_factor;
  y /= -scale_factor;
  x -= 1;
  y += 8;
  Position pos(x, y);
  position = pos;
}

void CoordinateTransformer::position2Pixel(const Position &position,
                                           PixelCoordinate &pixel,
                                           int scale_factor) {
  int x = position.x(), y = position.y();
  x += 1;
  y -= 8;
  x *= scale_factor;
  y *= -scale_factor;
  x /= 10;
  y /= 10;
  PixelCoordinate pc(x, y);
  pixel = pc;
}
