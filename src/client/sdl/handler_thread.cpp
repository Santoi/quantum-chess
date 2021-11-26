#include "handler_thread.h"

HandlerThread::HandlerThread()
                :open(false) {
}

HandlerThread::HandlerThread(bool open_)
                :open(open_) {
}

bool HandlerThread::isOpen() {
    return open;
}

