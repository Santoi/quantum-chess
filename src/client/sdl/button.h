#ifndef QUANTUM_CHESS_PROJ_BUTTON_H
#define QUANTUM_CHESS_PROJ_BUTTON_H

#include "pixel_coordinate.h"

class Button {

public:
    Button() = default;

    bool pixelIsOnButton(const PixelCoordinate& pixel_);
};

#endif //QUANTUM_CHESS_PROJ_BUTTON_H
