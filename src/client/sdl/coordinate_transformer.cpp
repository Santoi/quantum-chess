#include "coordinate_transformer.h"

void CoordinateTransformer::pixel2Position(const PixelCoordinate &pixel,
                                           BoardPosition &position, int width,
                                           int height) {
  // TODO emprolijar
  int x = (pixel.x() - (width / 2.0 - 4.0 * height / 10.0)) / (height / 10.0);
  int y = (pixel.y() / (height / 10.0) - 8) * (-1) + 1;
  BoardPosition pos(x, y);
  position = pos;
}

void CoordinateTransformer::position2Pixel(const BoardPosition &position,
                                           PixelCoordinate &pixel, int width,
                                           int height) {
  int x = height / 10 * position.x() + width / 2 - 4 * height / 10;
  int y = (8 - position.y()) * height / 10;
  PixelCoordinate pc(x, y);
  pixel = pc;
}
