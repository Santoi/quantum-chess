#include "action_thread.h"
#include "../../server/src/instructions/instruction.h"

ActionThread::ActionThread(BlockingQueue<RemoteClientInstruction> & instructions_,
                           Scene &scene_)
        :Thread(), instructions(instructions_), scene(scene_) {
}

void ActionThread::run() {
    try {
        while (true) {
            std::shared_ptr<RemoteClientInstruction> ptr_instruction;
            instructions.pop(ptr_instruction);
            ptr_instruction->makeAction(scene);
        }
    }
    catch(const BlockingQueueClosed & e) {}
}
