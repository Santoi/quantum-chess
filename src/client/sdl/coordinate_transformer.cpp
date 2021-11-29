#include "coordinate_transformer.h"

void CoordinateTransformer::pixel2Position(const PixelCoordinate &pixel,
                                           Position &position, int width,
                                           int height) {
  int x = pixel.x(), y = pixel.y();
  x *= 10;
  y *= 10;
  x /= height;
  y /= -height;
  x -= (width * 10) / (2 * height) - 4;
  y += 8;
  Position pos(x, y);
  position = pos;
}

void CoordinateTransformer::position2Pixel(const Position &position,
                                           PixelCoordinate &pixel, int width,
                                           int height) {

  std::cerr << "pos2pixel" << std::endl;
  int x = position.x(), y = position.y();
  std::cerr << "pos: " << x << " " << y << std::endl;
  x += (width * 10) / (2 * height) - 4;
  y -= 8;
  x *= height;
  y *= -height;
  x /= 10;
  y /= 10;
  std::cerr << "pixel: " << x << " " << y << std::endl;
  PixelCoordinate pc(x, y);
  pixel = pc;
}
