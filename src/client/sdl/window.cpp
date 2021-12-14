#include "window.h"
#include <SDL2pp/SDL2pp.hh>

#define WINDOW_MIN_RATIO 1.5

#ifndef QCHESS_PATH
#define QCHESS_PATH ""
#endif

#define ICON_PATH "resources/icons/quantum_logo.png"

Window::Window(int width, int height) :
    sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO),
    mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096),
    window_("Quantum Chess",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_RESIZABLE),
    renderer_(window_),
    sound_handler_(mixer) {
  SDL2pp::Surface icon(QCHESS_PATH ICON_PATH);
  window_.SetIcon(icon);
  window_.SetMinimumSize(width, height);
  window_.SetMaximumSize(SDL_MAX_SINT32, width / WINDOW_MIN_RATIO);
}

SDL2pp::Window &Window::window() {
  return window_;
}

Renderer &Window::renderer() {
  return renderer_;
}

SoundHandler &Window::sound_handler() {
  return sound_handler_;
}

size_t Window::getWidth() const {
  return window_.GetDrawableWidth();
}

size_t Window::getHeight() const {
  return window_.GetDrawableHeight();
}

void Window::setMaxHeight(size_t height) {
  window_.SetMaximumSize(SDL_MAX_SINT32, height);
}

double Window::getMinRatio() const {
  return WINDOW_MIN_RATIO;
}
