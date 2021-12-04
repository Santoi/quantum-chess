#ifndef QUANTUM_CHESS_PROJ_SCENE_H
#define QUANTUM_CHESS_PROJ_SCENE_H


#include "window.h"

class Scene {
protected:
  Window &window;

public:
  explicit Scene(Window &window);
  virtual void render() = 0;
};


#endif //QUANTUM_CHESS_PROJ_SCENE_H
