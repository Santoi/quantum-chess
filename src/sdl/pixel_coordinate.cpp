#include "pixel_coordinate.h"

PixelCoordinate::PixelCoordinate(uint32_t x, uint32_t y): x_(x), y_(y) {}

bool operator<(const PixelCoordinate &a, const PixelCoordinate &b) {
  return (a.x_ < b.x_) ||
         ((a.x_ == b.x_) && (a.y_ < b.y_));
}

uint32_t PixelCoordinate::x() const {
  return x_;
}

uint32_t PixelCoordinate::y() const {
  return y_;
}

