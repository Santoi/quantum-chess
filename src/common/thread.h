#ifndef QUANTUM_CHESS_PROJ_THREAD_H
#define QUANTUM_CHESS_PROJ_THREAD_H

#include <thread>

//Threads interface taken from Taller de programacion’s class

class Thread {
private:
  std::thread thread;

public:
  Thread();

  Thread(Thread &&other_thread) noexcept;

  // Starts new thread
  void start();

  // Joins Thread's thread
  void join();

  virtual ~Thread() = default;

protected:
  virtual void run() = 0;

  // Calls pure virtual protected method run(),
  // catching any exception that may rise.
  virtual void runCatchingExceptions();
};

#endif //QUANTUM_CHESS_PROJ_THREAD_H
