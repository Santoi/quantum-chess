#ifndef QUANTUM_CHESS_PROJ_PIXEL_COORDINATE_H
#define QUANTUM_CHESS_PROJ_PIXEL_COORDINATE_H

#include <cstdint>

class PixelCoordinate {
private:
  uint32_t x_, y_;

public:
  PixelCoordinate();

  PixelCoordinate(uint32_t x, uint32_t y);

  PixelCoordinate(const PixelCoordinate &orig) = default;

  PixelCoordinate &operator=(const PixelCoordinate &other) = default;

  friend bool operator<(const PixelCoordinate &a, const PixelCoordinate &b);

  uint32_t x() const;

  uint32_t y() const;

  void operator()(uint32_t x, uint32_t y);
};


#endif //QUANTUM_CHESS_PROJ_PIXEL_COORDINATE_H
