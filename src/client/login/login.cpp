#include "login.h"
#include "../communication/client_protocol.h"
#include "../../common/client_data.h"
#include "../../common/unique_ptr.h"
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <vector>

Login::Login()
    : client_socket_ptr(nullptr), role(ClientData::ROLE_SPECTATOR) {
}

void Login::connectToServer(const std::string &ip_, const std::string &port_) {
  const char *ip_ptr = ip_.c_str();
  const char *port_ptr = port_.c_str();
  client_socket_ptr = make_unique<Socket>(
          (Socket::createAConnectedSocket(ip_ptr, port_ptr)));
  ip = ip_;
  port = port_;
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

void Login::sendChosenMatchToServer(int match_number) {
  ClientProtocol protocol;
  protocol.sendChosenGame(*client_socket_ptr, match_number);
}

void Login::saveNickName(const std::string &nick_name) {
  client_nick_name = nick_name;
}

std::list<ClientData::Role> Login::getAvailableRolesFromServer() {
  std::list<ClientData::Role> available_roles;
  ClientProtocol protocol;
  protocol.getAvailableRoles(*client_socket_ptr, available_roles);
  return available_roles;
}

void Login::sendSavedNickNameToServer() {
  ClientProtocol protocol;
  protocol.sendClientsNickName(*client_socket_ptr, client_nick_name);
}

void Login::saveAndSendChosenRoleToServer(ClientData::Role role_) {
  ClientProtocol protocol;
  protocol.sendChosenRole(*client_socket_ptr, role_);
  role = role_;
}

ClientData::Role Login::getRole() {
  return role;
}

void Login::reconnectToServer() {
  client_socket_ptr->shutdownAndClose();
  const char *ip_ptr = ip.c_str();
  const char *port_ptr = port.c_str();
  client_socket_ptr = make_unique<Socket>(
            (Socket::createAConnectedSocket(ip_ptr, port_ptr)));
}

