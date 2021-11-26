#ifndef QUANTUM_CHESS_PROJ_LOGIN_H
#define QUANTUM_CHESS_PROJ_LOGIN_H

#include "pixel_coordinate.h"
#include "../../common/src/blocking_queue.h"

#include <string>

class Login {
private:
    BlockingQueue<std::string>& queue;

public:
    Login() = delete;

    Login(BlockingQueue<std::string>& queue_);

    bool pixelIsOnBottom(const PixelCoordinate& pixel_);
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_H
