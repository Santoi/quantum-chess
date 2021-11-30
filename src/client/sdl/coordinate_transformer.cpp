#include "coordinate_transformer.h"

void CoordinateTransformer::pixel2Position(const PixelCoordinate &pixel,
                                           Position &position, int width,
                                           int height) {
  // TODO SANTI ACA PARCHEE PARA QUE ANDE. FIJATE SI LO PODES MEJORAR ?
  int x = pixel.x(), y = pixel.y();
  x = (x - (width / 2.0 - 4.0 * height / 10.0)) / (height / 10.0);
  y = (y / (height / 10.0) - 8) * (-1) + 1;
  Position pos(x, y);
  position = pos;
}

void CoordinateTransformer::position2Pixel(const Position &position,
                                           PixelCoordinate &pixel, int width,
                                           int height) {

  int x = position.x(), y = position.y();
  x = height / 10 * x + width / 2 - 4 * height / 10;
  y = (8 - y) * height / 10;
  PixelCoordinate pc(x, y);
  pixel = pc;
}
