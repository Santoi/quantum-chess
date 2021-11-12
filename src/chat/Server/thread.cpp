#include "thread.h"

Thread::Thread(Thread&& otherThread)
        :thread(std::move(otherThread.thread)){
}


void Thread::start() {
    this->thread = std::thread(&Thread::runCatchingExceptions, this);
}

void Thread::join() {
    this->thread.join();
}

void Thread::runCatchingExceptions() {
    this->run();
}

Thread::~Thread() {
}