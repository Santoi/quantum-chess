#include "login.h"

Login::Login(BlockingQueue<std::string>& queue_)
        :queue(queue_){
}

bool Login::pixelIsOnBottom(const PixelCoordinate& pixel_) {
    return false;
}
