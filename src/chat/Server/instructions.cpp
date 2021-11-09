#include "instructions.h"

void Instruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {

}


ChatInstruction::ChatInstruction(std::string&& message)
                :message(std::move(message)) {
}


void ChatInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {

}

void MovementInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {

}
