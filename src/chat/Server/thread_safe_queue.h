#ifndef TP2FINAL_THREADSAFEQUEUE_H
#define TP2FINAL_THREADSAFEQUEUE_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "instructions.h"

class ThreadSafeQueue {
    std::queue<std::shared_ptr<Instruction>> queue;
    std::mutex mutex;
    std::condition_variable condition_variable;

public:
    ThreadSafeQueue();

    ThreadSafeQueue(ThreadSafeQueue&& other_queue);
    //Se agrega el elemento info a la cola. Se lockea el mutex
    //correspondientemente para almacenar dicha información de forma válida. Se
    //notifican a todos los hilos expectantes de hacer pop() que se agregó un
    //nuevo objeto.
    void push(std::shared_ptr<Instruction> instruc_ptr);

    //Se saca el primer elemento de la cola. En un ambiente de concurrencia,
    //puede ser que un hilo quiera hacer un pop cuando la cola está vacía. Se
    //espera entonces a que otro hilo haga un push a la cola para recibir la
    //notificación y, con el lock activado poder extraer la información
    //correspondientemente, guardándola en la info pasada por referencia.
    void pop(std::shared_ptr<Instruction>& instruc_ptr);

    ~ThreadSafeQueue();
};

#endif //TP2FINAL_THREADSAFEQUEUE_H
