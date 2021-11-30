#ifndef QUANTUM_CHESS_PROJ_ACTION_THREAD_H
#define QUANTUM_CHESS_PROJ_ACTION_THREAD_H

#include <thread>
#include "remote_client_instructions.h"
#include "../../common/src/blocking_queue.h"
#include "../../common/src/thread.h"

//Threads interface taken from Taller de programacion’s class

class ActionThread : public Thread {
  BlockingQueue<RemoteClientInstruction> &instructions;
  Game &game;
  Chat &chat;
  ChessLog &chess_log;

public:
  ActionThread(BlockingQueue<RemoteClientInstruction> &instructions_,
               Game &game_, Chat &chat_, ChessLog &chess_log_);


  void run() override;
};

#endif //QUANTUM_CHESS_PROJ_ACTION_THREAD_H
