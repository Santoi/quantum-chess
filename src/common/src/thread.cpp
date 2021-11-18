#include <iostream>
#include "thread.h"

Thread::Thread(): thread(){
}

Thread::Thread(Thread&& other_thread)
        :thread(std::move(other_thread.thread)){
}

void Thread::start() {
    this->thread = std::thread(&Thread::runCatchingExceptions, this);
}

void Thread::join() {
    this->thread.join();
}

bool Thread::isJoinable() {
    return thread.joinable();
}

void Thread::runCatchingExceptions() {
    try {
        this->run();
    }
    catch (const std::exception & e){
        std::cerr << "Error:" << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Error desconocido" << std::endl;
    }
}