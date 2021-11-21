#include "renderer.h"
#include "sprite.h"
#include "scene.h"
#include <SDL2pp/SDL2pp.hh>
#include <algorithm>

Renderer::Renderer(SDL2pp::Window &window): renderer_(window,
                                             -1,
                                             SDL_RENDERER_ACCELERATED) {
}

void Renderer::copy(Sprite &sprite, int x, int y) {
  const SDL2pp::Rect dest(x, y, sprite.width(), sprite.height());
  renderer_.Copy(sprite.sprite(), SDL2pp::NullOpt, dest);
}

void Renderer::copy(Sprite &sprite, int x_src, int y_src, int x_dst,
                    int y_dst, int width, int height) {
  const SDL2pp::Rect src(x_src, y_src, width, height);
  const SDL2pp::Rect dest(x_dst, y_dst, sprite.width(), sprite.height());
  renderer_.Copy(sprite.sprite(), src, dest);
}

void Renderer::render(Scene &scene) {
  renderer_.Clear();
  scene.setScale(getMinDimension());
  scene.render();
  renderer_.Present();
}

SDL2pp::Renderer &Renderer::renderer() {
  return renderer_;
}

int Renderer::getMinDimension() {
  return std::min(renderer_.GetOutputWidth(), renderer_.GetOutputHeight());
}
