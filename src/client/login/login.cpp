#include "login.h"
#include "../communication/client_protocol.h"
#include "../../common/client_data.h"
#include "../../common/unique_ptr.h"
#include <iostream>

Login::Login()
    : client_socket_ptr(nullptr) {
}

void Login::connectToServer(const std::string &ip_, const std::string &port_) {
  const char *ip = ip_.c_str();
  const char *port = port_.c_str();
  client_socket_ptr = make_unique<Socket>(
      (Socket::createAConnectedSocket(ip, port)));
}

void Login::getListOfMatchesInfo(
    std::map<uint16_t, std::vector<ClientData>> &match_info) {
  ClientProtocol protocol;
  match_info = protocol.receiveMatchesInfo(*client_socket_ptr);
}

void
Login::refreshMatches() {
  ClientProtocol protocol;
  protocol.sendChosenGame(*client_socket_ptr, UINT16_MAX);
}

Socket Login::getClientSocket() {
  return std::move(*client_socket_ptr);
}

std::string Login::getClientNickName() {
  return client_nick_name;
}

void Login::chooseMatchNumber(int match_number) {
  ClientProtocol protocol;
  protocol.sendChosenGame(*client_socket_ptr, match_number);
}

void Login::saveNickName(const std::string &nick_name) {
  client_nick_name = nick_name;
}

std::list<ClientData::Role> Login::getAvailableRoles() {
  std::list<ClientData::Role> available_roles;
  ClientProtocol protocol;
  protocol.getAvailableRoles(*client_socket_ptr, available_roles);
  return available_roles;
}

void Login::sendSavedNickNameToServer() {
  ClientProtocol protocol;
  protocol.sendClientsNickName(*client_socket_ptr, client_nick_name);
}

void Login::sendChosenRole(ClientData::Role role_) {
  ClientProtocol protocol;
  protocol.sendChosenRole(*client_socket_ptr, role_);
  role = role_;
}

ClientData::Role Login::getRole() {
  return role;
}

