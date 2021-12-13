#ifndef QUANTUM_CHESS_PROJ_HANDLER_THREAD_H
#define QUANTUM_CHESS_PROJ_HANDLER_THREAD_H

#include "../../common/thread.h"
#include <atomic>

class HandlerThread: public Thread {
protected:
    std::atomic<bool> open;

public:
    HandlerThread();

    HandlerThread(bool open_);

    //Returns open boolean.
    bool isOpen();

    ~HandlerThread() = default;

private:

    virtual void run() = 0;
};

#endif //QUANTUM_CHESS_PROJ_HANDLER_THREAD_H
