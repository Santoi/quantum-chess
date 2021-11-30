#ifndef QUANTUM_CHESS_PROJ_CHAT_H
#define QUANTUM_CHESS_PROJ_CHAT_H

#include <utility>

#include "message_container.h"
#include "../../common/src/blocking_queue.h"
#include "../communication/remote_client_instructions.h"

#define MAX_MESSAGES 10

class Chat {
public:
  typedef struct ChatMessage {
    const std::string client_id;
    const std::string nickname;
    const std::string message;
    const std::string timestamp;

    ChatMessage(uint16_t client_id, std::string nickname, std::string message,
                std::string timestamp) : client_id(std::to_string(client_id)),
                                         nickname(std::move(nickname)),
                                         message(std::move(message)),
                                         timestamp(std::move(timestamp)) {}
  } ChatMessage;

private:
  MessageContainer<ChatMessage> messages;
  BlockingQueue<RemoteClientInstruction> &send_queue;

public:
  explicit Chat(BlockingQueue<RemoteClientInstruction> &send_queue_);

  void addMessage(ChatMessage &&chat_message);

  void sendMessage(const std::string &message);
};


#endif //QUANTUM_CHESS_PROJ_CHAT_H
