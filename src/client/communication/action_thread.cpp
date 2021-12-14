#include "action_thread.h"

ActionThread::ActionThread(
    BlockingQueue<RemoteClientInstruction> &instructions_, Game &game_,
    Chat &chat_, ChessLog &chess_log_, ErrorLog &error_log_,
    TurnLog &turn_log_)
    : Thread(), instructions(instructions_), game(game_), chat(chat_),
      chess_log(chess_log_), error_log(error_log_), turn_log(turn_log_) {
}

void ActionThread::run() {
  try {
    while (true) {
      auto ptr_instruction = instructions.pop();
      ptr_instruction->makeAction(game, chat, chess_log, error_log,
                                  turn_log);
    }
  }
  catch(const BlockingQueueClosed &e) {}
}

