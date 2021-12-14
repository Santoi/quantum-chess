#ifndef QUANTUM_CHESS_PROJ_CHAT_H
#define QUANTUM_CHESS_PROJ_CHAT_H

#include <utility>

#include "../../common/blocking_queue.h"
#include "../communication/remote_client_instructions.h"
#include  "../sdl/game_scene.h"
#include <string>

#define MAX_MESSAGES 10

class Chat {
private:
  BlockingQueue<RemoteClientInstruction> &send_queue;
  GameScene &scene;

public:
  explicit Chat(BlockingQueue<RemoteClientInstruction> &send_queue_,
                GameScene &scene);

  // Send chat message to the Server by pushing it into the send queue
  void sendMessage(const std::string &message);

  // Add message to the chat. Shows nick mane, ID, server's timestamp and msg
  void addMessage(uint16_t client_id, std::string nickname, std::string message,
                  std::string timestamp);

  // Enables text input from user if pixel is inside the text box
  bool enableIfPixelIsInChat(const PixelCoordinate &pixel);

  // Disable input from user
  void disable();
};


#endif //QUANTUM_CHESS_PROJ_CHAT_H
