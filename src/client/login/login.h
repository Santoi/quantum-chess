#ifndef QUANTUM_CHESS_PROJ_LOGIN_H
#define QUANTUM_CHESS_PROJ_LOGIN_H

#include "../sdl/pixel_coordinate.h"
#include "../../common/src/blocking_queue.h"
#include "../../common/src/socket.h"
#include "../sdl/button.h"
#include <memory>
#include <vector>
#include <mutex>
#include <string>

class Login {
private:
  std::mutex mutex;
  std::unique_ptr<Socket> client_socket_ptr;
  std::string client_nick_name;
  ClientData::Role role;

public:
  Login();

  void connectToServer(const std::string &ip, const std::string &port);

  void saveNickName(const std::string &nick_name);

  void sendSavedNickNameToServer();

  Socket getClientSocket();

  std::string getClientNickName();

  std::list<ClientData::Role> getAvailableRoles();

  void sendChosenRole(ClientData::Role role_);

  void chooseMatchNumber(int match_number);

  ~Login() = default;

  void
  getListOfMatchesInfo(std::map<uint16_t, std::vector<ClientData>> &match_info);

  ClientData::Role getRole();

  void refreshMatches();
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_H
