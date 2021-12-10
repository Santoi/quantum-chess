#ifndef QUANTUM_CHESS_PROJ_CHAT_H
#define QUANTUM_CHESS_PROJ_CHAT_H

#include <utility>

#include "../../common/src/blocking_queue.h"
#include "../communication/remote_client_instructions.h"
#include  "../sdl/game_scene.h"

#define MAX_MESSAGES 10

class Chat {
private:
  BlockingQueue<RemoteClientInstruction> &send_queue;
  GameScene &scene;

public:
  explicit Chat(BlockingQueue<RemoteClientInstruction> &send_queue_,
                GameScene &scene);

  void sendMessage(const std::string &message);

  void addMessage(uint16_t client_id, std::string nickname, std::string message,
                  std::string timestamp);

  bool enableIfPixelIsInChat(PixelCoordinate &pixel);

  void disable();
};


#endif //QUANTUM_CHESS_PROJ_CHAT_H
