#include "login.h"

Login::Login()
        :client_socket_ptr(nullptr) {
}

/*
void Login::pressButtonThatHasPixel(const PixelCoordinate& pixel_) {
    std::string result;
    if (!client_is_connected_to_server) {
       try {
           //get info from text fields network container (ip, port, nick name)
           char* ip = nullptr;
           char* port = nullptr;
           Socket::createAConnectedSocketPointedByUniquePointer(client_socket_ptr, ip, port);
       } catch (...) {

       }
    }
}*/

Socket Login::getClientSocket() {
    return std::move(*client_socket_ptr);
}

std::string Login::getClientNickName() {
    return std::move(client_nick_name);
}