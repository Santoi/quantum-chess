#ifndef QUANTUM_CHESS_PROJ_WINDOW_H
#define QUANTUM_CHESS_PROJ_WINDOW_H

#include <SDL2pp/SDL2pp.hh>

class Window {
private:
  SDL2pp::Window window_;
public:
  Window();
  SDL2pp::Window& window();
};


#endif //QUANTUM_CHESS_PROJ_WINDOW_H
