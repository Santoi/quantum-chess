#ifndef QUANTUM_CHESS_PROJ_LOGIN_H
#define QUANTUM_CHESS_PROJ_LOGIN_H

#include "../sdl/pixel_coordinate.h"
#include "../../common/blocking_queue.h"
#include "../../common/socket.h"
#include "../logic/button.h"
#include <memory>
#include <vector>
#include <mutex>
#include <string>
#include <map>
#include <list>

class Login {
private:
  std::unique_ptr<Socket> client_socket_ptr;
  std::string ip;
  std::string port;
  std::string client_nick_name;
  ClientData::Role role;

public:
  Login();

  //Creates a socket using the given ip and port. If either of them
  //are invalid, exception NetworkAddressInfoException is thrown.
  void connectToServer(const std::string &ip, const std::string &port);

  void saveNickName(const std::string &nick_name);

  void sendSavedNickNameToServer();

  //Return moved socket.
  Socket getClientSocket();

  std::list<ClientData::Role> getAvailableRolesFromServer();

  void saveAndSendChosenRoleToServer(ClientData::Role role_);

  void sendChosenMatchToServer(int match_number);

  ~Login() = default;

  void
  getListOfMatchesInfo(std::map<uint16_t, std::vector<ClientData>> &match_info);

  ClientData::Role getRole();

  //Sends to server the refresh matches instruction.
  void refreshMatches();

    void reconnectToServer();
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_H
