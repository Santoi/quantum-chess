#ifndef QUANTUM_CHESS_PROJ_THREAD_H
#define QUANTUM_CHESS_PROJ_THREAD_H

#include <thread>

//Threads interface taken from Taller de programacion’s class

class Thread {
private:
    std::thread thread;

public:
    Thread() = default;
    Thread(Thread&& otherThread);
    void start();
    void join();
    void runCatchingExceptions();
    virtual ~Thread();

protected:
    virtual void run() = 0;
};



#endif //QUANTUM_CHESS_PROJ_THREAD_H
