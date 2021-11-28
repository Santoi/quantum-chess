#ifndef QUANTUM_CHESS_PROJ_BUTTON_H
#define QUANTUM_CHESS_PROJ_BUTTON_H

#include "pixel_coordinate.h"
#include <list>
#include <string>
class Button {

public:
    Button() = default;

    bool fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens);

};

#endif //QUANTUM_CHESS_PROJ_BUTTON_H
