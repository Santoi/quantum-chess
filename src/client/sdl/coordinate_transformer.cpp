#include "coordinate_transformer.h"

CoordinateTransformer::CoordinateTransformer() : flipped(false) {}

CoordinateTransformer::CoordinateTransformer(bool flipped_) : flipped(
        flipped_) {

}

void CoordinateTransformer::pixel2Position(const PixelCoordinate &pixel,
                                           Position &position, int width,
                                           int height) {
  int x = (pixel.x() - (width / 2.0 - 4.0 * height / 10.0)) / (height / 10.0);
  int y = (pixel.y() / (height / 10.0) - 8) * (-1) + 1;
  Position pos((!flipped || x < 0) ? x : 7 - x,
               (!flipped || y < 0) ? y : 7 - y);
  position = pos;
}

void CoordinateTransformer::position2Pixel(const Position &position,
                                           PixelCoordinate &pixel, int width,
                                           int height) {
  int flipped_x = position.x();
  int flipped_y = position.y();
  if (flipped && flipped_y >= 0)
    flipped_y = 7 - flipped_y;
  if (flipped && flipped_x >= 0)
    flipped_x = 7 - flipped_x;
  int x = height / 10 * flipped_x + width / 2 - 4 * height / 10;
  int y = (8 - flipped_y) * height / 10;
  PixelCoordinate pc(x, y);
  pixel = pc;

}

void CoordinateTransformer::flip() {
  flipped = !flipped;
}
