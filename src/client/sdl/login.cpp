#include "login.h"

Login::Login()
        :client_socket_ptr(nullptr) {
}

void Login::connectToServer(const std::string& ip_, const std::string& port_) {
    const char* ip = ip_.c_str();
    const char* port = port_.c_str();
    Socket::createAConnectedSocket(client_socket_ptr, ip, port);
}


Socket Login::getClientSocket() {
    return std::move(*client_socket_ptr);
}

std::string Login::getClientNickName() {
    return std::move(client_nick_name);
}