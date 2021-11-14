#include "thread.h"

Thread::Thread()
        :has_active_thread(false) {
}

Thread::Thread(Thread&& other_thread)
        :thread(std::move(other_thread.thread)), has_active_thread(other_thread.has_active_thread){
}


void Thread::start() {
    this->thread = std::thread(&Thread::runCatchingExceptions, this);
    this->has_active_thread = true;
}

void Thread::join() {
    this->thread.join();
}

bool Thread::isJoinable() {
    return this->has_active_thread;
}


void Thread::runCatchingExceptions() {
    try {
        this->run();
    } catch (...) {
        
    }
}

Thread::~Thread() {
}