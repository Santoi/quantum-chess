#include "chat.h"

Chat::Chat(BlockingQueue<RemoteClientInstruction> &send_queue_)
        : messages(MAX_MESSAGES),
          send_queue(send_queue_) {}

void Chat::sendMessage(const std::string &message) {
  auto instruction = std::make_shared<RemoteClientChatInstruction>(message);
  send_queue.push(instruction);
}

void Chat::addMessage(ChatMessage &&chat_message) {
  messages.add(std::move(chat_message));
}
