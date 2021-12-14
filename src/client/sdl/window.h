#ifndef QUANTUM_CHESS_PROJ_WINDOW_H
#define QUANTUM_CHESS_PROJ_WINDOW_H

#include "renderer.h"
#include "sound_handler.h"
#include <SDL2pp/SDL2pp.hh>
#include <mutex>

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 720

class Window {
private:
  SDL2pp::SDL sdl;
  SDL2pp::Mixer mixer;
  SDL2pp::Window window_;
  Renderer renderer_;
  SoundHandler sound_handler_;

public:
  explicit Window(int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);

  SDL2pp::Window &window();

  Renderer &renderer();

  SoundHandler &sound_handler();

  size_t getWidth() const;

  size_t getHeight() const;

  double getMinRatio() const;

  void setMaxHeight(size_t height);

};


#endif //QUANTUM_CHESS_PROJ_WINDOW_H
