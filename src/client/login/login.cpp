#include "login.h"
#include "../communication/client_protocol.h"
#include "../../common/src/client_data.h"
#include "../../common/src/unique_ptr.h"
#include <iostream>

Login::Login()
    : client_socket_ptr(nullptr) {
}

void Login::connectToServer(const std::string &ip_, const std::string &port_) {
  const char *ip = ip_.c_str();
  const char *port = port_.c_str();
  *client_socket_ptr = Socket::createAConnectedSocket(ip, port);
}

void Login::getListOfMatchesInfo(
    std::map<uint16_t, std::vector<ClientData>> &match_info) {
  ClientProtocol protocol;
  match_info = protocol.receiveMatchesInfo(*client_socket_ptr);
}

Socket Login::getClientSocket() {
  return std::move(*client_socket_ptr);
}

std::string Login::getClientNickName() {
  return client_nick_name;
}

void Login::chooseMatchNumber(int match_number) {
  ClientProtocol protocol;
  std::cout << "Me conecto a la partida " << match_number << std::endl;
  protocol.sendChosenGame(*client_socket_ptr, match_number);
}
