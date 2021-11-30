#include "action_thread.h"
#include "../../server/src/instructions/instruction.h"

ActionThread::ActionThread(
        BlockingQueue<RemoteClientInstruction> &instructions_,
        Game &game_, Chat &chat_, ChessLog &chess_log_)
        : Thread(), instructions(instructions_), game(game_), chat(chat_),
          chess_log(chess_log_) {
}

void ActionThread::run() {
  try {
    while (true) {
      std::shared_ptr<RemoteClientInstruction> ptr_instruction;
      instructions.pop(ptr_instruction);
      ptr_instruction->makeAction(game, chat, chess_log);
    }
  }
  catch (const BlockingQueueClosed &e) {}
}

