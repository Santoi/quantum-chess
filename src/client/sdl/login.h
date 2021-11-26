#ifndef QUANTUM_CHESS_PROJ_LOGIN_H
#define QUANTUM_CHESS_PROJ_LOGIN_H

#include "pixel_coordinate.h"
#include "scene.h"
#include "../../common/src/blocking_queue.h"
#include "../../common/src/socket.h"
#include "button.h"
#include "../sdl/window.h"
#include <memory>
#include <vector>
#include <mutex>
#include <string>

class Login: public Scene {
private:
    std::mutex mutex;
    std::unique_ptr<Socket> client_socket_ptr;
    bool client_is_connected_to_match;
    bool client_is_connected_to_server;
    Button connect_to_server_button;
    std::string client_nick_name;

public:
    Login() = delete;

    Login(Window& window);

    bool clientIsConnectedToMatch();

    void setScale(int scale_) override;

    void render() override;

    bool pixelIsOnAButton(const PixelCoordinate& pixel_);

    void pressButtonThatHasPixel(const PixelCoordinate& pixel_);

    Socket getClientSocket();

    std::string getClientNickName();

private:
    void renderGetIPandPort();
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_H
