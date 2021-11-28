#include "window.h"
#include <SDL2pp/SDL2pp.hh>

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640

Window::Window() :
    sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO),
    mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096),
    window_("Quantum Chess",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            DEFAULT_WIDTH, DEFAULT_HEIGHT,
            SDL_WINDOW_RESIZABLE),
    renderer_(window_),
    sound_handler_(mixer) {}

SDL2pp::Window &Window::window() {
  return window_;
}

Renderer &Window::renderer() {
  return renderer_;
}

SoundHandler &Window::sound_handler() {
  return sound_handler_;
}
