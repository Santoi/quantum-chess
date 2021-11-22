#include "action_thread.h"
#include "../../server/src/instructions/instruction.h"
#include "../sdl/event_handler.h"

ActionThread::ActionThread(BlockingQueue<RemoteClientInstruction> & instructions_,
                           Game &game_)
        :Thread(), instructions(instructions_), game(game_) {
}

void ActionThread::run() {
    try {
        while (true) {
            std::shared_ptr<RemoteClientInstruction> ptr_instruction;
            instructions.pop(ptr_instruction);
            ptr_instruction->makeAction(game);
        }
    }
    catch(const BlockingQueueClosed & e) {}
}

