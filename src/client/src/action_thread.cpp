#include "action_thread.h"
#include "../../server/src/instructions/instruction.h"

ActionThread::ActionThread(BlockingQueue<RemoteClientInstruction> & instructions_,
                           AsciiBoard & board_)
        :Thread(), instructions(instructions_), board(board_) {
}

void ActionThread::run() {
    while (true) {
        std::shared_ptr<RemoteClientInstruction> ptr_instruction;
        instructions.pop(ptr_instruction);
        ptr_instruction->makeAction(board);
    }
}
