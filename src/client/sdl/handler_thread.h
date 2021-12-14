#ifndef QUANTUM_CHESS_PROJ_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_HANDLER_THREAD_H

#include "../../common/thread.h"
#include <atomic>

class HandlerThread : public Thread {
protected:
  std::atomic<bool> open;

public:
  HandlerThread();

  explicit HandlerThread(bool open_);

  // Tells if thread is active
  bool isOpen();

  ~HandlerThread() override = default;
};

#endif //QUANTUM_CHESS_PROJ_HANDLER_THREAD_H
