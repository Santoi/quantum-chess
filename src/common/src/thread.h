#ifndef QUANTUM_CHESS_PROJ_THREAD_H
#define QUANTUM_CHESS_PROJ_THREAD_H

#include <thread>

//Threads interface taken from Taller de programacion’s class

class Thread {
private:
    std::thread thread;

protected:

public:
    //Creates thread object. has_active_thread is set to false.
    Thread();

    //Moves other_thread thread to new thread, and copies the has_active_thread boolean.
    Thread(Thread&& other_thread);

    //Starts new thread by calling Thread::runCatchingExceptions. has_active_thread is set to true.
    void start();

    //Joins Thread's thread. If the object does not have an active thread then it does nothing.
    void join();

    //Returns true if the object has an active thread and can be joined, or false othrewise.
    virtual bool isJoinable();

    //Calls pure virtual protected method run(), catching any exception that may rise.
    void runCatchingExceptions();

    //Default destructor
    virtual ~Thread() = default;

protected:
    //Method that any class that inherits this Thread class needs to implement.
    virtual void run() = 0;
};

#endif //QUANTUM_CHESS_PROJ_ACTION_THREAD_H
