#ifndef QUANTUM_CHESS_PROJ_LOGIN_H
#define QUANTUM_CHESS_PROJ_LOGIN_H

#include "pixel_coordinate.h"
#include "../../common/src/blocking_queue.h"
#include "../../common/src/socket.h"
#include "button.h"
#include <memory>
#include <vector>
#include <mutex>
#include <string>

class Login {
private:
  std::mutex mutex;
  std::unique_ptr<Socket> client_socket_ptr;
  std::string client_nick_name;

public:

  Login();

  void connectToServer(const std::string &ip, const std::string &port);

  Socket getClientSocket();

  std::string getClientNickName();

  ~Login() = default;
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_H
