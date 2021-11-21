#include "window.h"
#include <SDL2pp/SDL2pp.hh>

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640

Window::Window(): window_("Quantum Chess",
                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        DEFAULT_WIDTH, DEFAULT_HEIGHT,
                        SDL_WINDOW_RESIZABLE) {}

SDL2pp::Window& Window::window() {
  return window_;
}
