#include "chat.h"
#include  "../sdl/game_scene.h"

Chat::Chat(BlockingQueue<RemoteClientInstruction> &send_queue_,
           GameScene &scene)
        : send_queue(send_queue_), scene(scene) {}

void Chat::sendMessage(const std::string &message) {
  if (message.empty())
    return;
  auto instruction = std::make_shared<RemoteClientChatInstruction>(message);
  send_queue.push(instruction);
}

void
Chat::addMessage(uint16_t client_id, std::string nickname, std::string message,
                 std::string timestamp) {
  scene.addChatMessage(nickname, std::to_string(client_id), timestamp, message);
}


