#include "renderer.h"
#include "sprite.h"
#include "scene.h"
#include <SDL2pp/SDL2pp.hh>
#include <algorithm>

Renderer::Renderer(SDL2pp::Window &window) : renderer_(window,
                                                       -1,
                                                       SDL_RENDERER_ACCELERATED) {
}

void Renderer::copy(Sprite &sprite, size_t x, size_t y) {
  const SDL2pp::Rect dest(x, y, sprite.width(), sprite.height());
  renderer_.Copy(sprite.sprite(), SDL2pp::NullOpt, dest);
}

void Renderer::copy(Sprite &sprite, size_t x_src, size_t y_src, size_t x_dst,
                    size_t y_dst, size_t width, size_t height) {
  const SDL2pp::Rect src(x_src, y_src, width, height);
  const SDL2pp::Rect dest(x_dst, y_dst, sprite.width(), sprite.height());
  renderer_.Copy(sprite.sprite(), src, dest);
}

void Renderer::render(Scene &scene) {
  renderer_.Clear();
  scene.render();
  renderer_.Present();
}

SDL2pp::Renderer &Renderer::renderer() {
  return renderer_;
}

size_t Renderer::getMinDimension() const {
  return std::min(renderer_.GetOutputWidth(), renderer_.GetOutputHeight());
}

size_t Renderer::getWidth() const {
  return renderer_.GetOutputWidth();
}

size_t Renderer::getHeight() const {
  return renderer_.GetOutputHeight();
}
