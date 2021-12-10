#ifndef QUANTUM_CHESS_PROJ_WINDOW_H
#define QUANTUM_CHESS_PROJ_WINDOW_H

#include "renderer.h"
#include "sound/sound_handler.h"
#include <SDL2pp/SDL2pp.hh>
#include <mutex>


class Window {
private:
  SDL2pp::SDL sdl;
  SDL2pp::Mixer mixer;
  SDL2pp::Window window_;
  Renderer renderer_;
  SoundHandler sound_handler_;

public:
  Window();

  SDL2pp::Window &window();

  Renderer &renderer();

  SoundHandler &sound_handler();

  size_t getWidth() const;

  size_t getHeight() const;

  double getMinRatio() const;

  void setMaxHeight(size_t height);

  void setSize(size_t width, size_t height);
};


#endif //QUANTUM_CHESS_PROJ_WINDOW_H
