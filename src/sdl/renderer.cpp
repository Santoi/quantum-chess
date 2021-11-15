#include "renderer.h"
#include "window.h"
#include "sprite.h"
#include "scene.h"
#include <SDL2pp/SDL2pp.hh>
#include <iostream>

Renderer::Renderer(Window &window): renderer_(window.window(),
                                             -1,
                                             SDL_RENDERER_ACCELERATED) {
}

void Renderer::copy(Sprite &sprite, int x, int y) {
  const SDL2pp::Rect dest(x, y, sprite.width(), sprite.height());
  renderer_.Copy(sprite.sprite(), SDL2pp::NullOpt, dest);
}

void Renderer::clear() {
  renderer_.Clear();
}

void Renderer::render(Scene &scene) {
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
