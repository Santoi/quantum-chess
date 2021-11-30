#ifndef QUANTUM_CHESS_PROJ_CHAT_H
#define QUANTUM_CHESS_PROJ_CHAT_H

#include <utility>

#include "../../common/src/blocking_queue.h"
#include "../communication/remote_client_instructions.h"
#include  "../sdl/scene.h"

#define MAX_MESSAGES 10

class Chat {
private:
  BlockingQueue<RemoteClientInstruction> &send_queue;
  Scene &scene;

public:
  explicit Chat(BlockingQueue<RemoteClientInstruction> &send_queue_,
                Scene &scene);

  void sendMessage(const std::string &message);

  void addMessage(uint16_t client_id, std::string nickname, std::string message,
                  std::string timestamp);
};


#endif //QUANTUM_CHESS_PROJ_CHAT_H
