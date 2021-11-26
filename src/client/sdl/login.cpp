#include "login.h"

#define NUMBER_OF_BUTTONS 5
#define ENTER_IP_BUTTON 0
#define ENTER_PORT_BUTTON 1

Login::Login(Window& window)
        :Scene(window.renderer().getMinDimension()), client_socket_ptr(nullptr) {
}

bool Login::clientIsConnectedToMatch() {
    return client_is_connected_to_match;
}


void Login::setScale(int scale_) {
    scale = scale_;
}

void Login::render() {
    if (!client_is_connected_to_server)
        renderGetIPandPort();
}

void Login::renderGetIPandPort() {

    std::cout << "Ingresa el IP" << std::endl;
}


bool Login::pixelIsOnAButton(const PixelCoordinate& pixel_) {
    if (!client_is_connected_to_server)
        return connect_to_server_button.pixelIsOnButton(pixel_);
    return false;
}

void Login::pressButtonThatHasPixel(const PixelCoordinate& pixel_) {
    std::string result;
    if (!client_is_connected_to_server) {
       try {
           //get info from text fields (ip, port, nick name)
           char* ip = nullptr;
           char* port = nullptr;
           Socket::createAConnectedSocketPointedByUniquePointer(client_socket_ptr, ip, port);
       } catch (...) {

       }
    }
}

Socket Login::getClientSocket() {
    return std::move(*client_socket_ptr);
}

std::string Login::getClientNickName() {
    return std::move(client_nick_name);
}