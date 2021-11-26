#ifndef QUANTUM_CHESS_PROJ_LOBBY_H
#define QUANTUM_CHESS_PROJ_LOBBY_H

#include "pixel_coordinate.h"
#include "../../common/src/blocking_queue.h"

#include <std::string>

class Lobby {
private:
    BlockingQueue<std::string>& queue;

public:
    Lobby() = delete;

    Lobby(BlockingQueue<std::string>& queue_);

    bool pixelIsOnBottom(const PixelCoordinate& pixel_);
};

#endif //QUANTUM_CHESS_PROJ_LOBBY_H
