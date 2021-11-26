#ifndef QUANTUM_CHESS_PROJ_LOBBY_H
#define QUANTUM_CHESS_PROJ_LOBBY_H

#include "pixel_coordinate.h"


class Lobby {

public:
    Lobby();

    bool pixelIsOnBottom(const PixelCoordinate& pixel_);
};

#endif //QUANTUM_CHESS_PROJ_LOBBY_H
