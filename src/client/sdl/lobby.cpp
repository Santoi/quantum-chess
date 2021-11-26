#include "lobby.h"

Lobby::Lobby(BlockingQueue<std::string>& queue_)
        :queue(queue_){
}

bool Lobby::pixelIsOnBottom(const PixelCoordinate& pixel_) {
    return false;
}
