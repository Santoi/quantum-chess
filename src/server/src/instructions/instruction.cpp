#include "instruction.h"
#include "../blocking_queue.h"
#include "../client_handler.h"


void Instruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues,
                                                        std::vector<ClientHandler>& clients) {}





/*
void MovementInstruction::makeActionAndNotifyAllListeningQueues(std::list<BlockingQueue>& listening_queues) {

}

void MovementInstruction::fillPacketWithInstructionsToSend(Packet& packet) {

}*/
