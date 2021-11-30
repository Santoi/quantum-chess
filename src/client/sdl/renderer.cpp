#include "renderer.h"
#include "sprite.h"
#include "../game/game.h"
#include "login_renderer.h"
#include <SDL2pp/SDL2pp.hh>
#include <algorithm>

Renderer::Renderer(SDL2pp::Window &window) : renderer_(window,
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

void Renderer::render(LoginRenderer& login_renderer) {
    renderer_.Clear();
    login_renderer.setScale(getMinDimension());
    login_renderer.render();
    renderer_.Present();
}

void Renderer::render(Game &game) {
  renderer_.Clear();
  game.setScale(getMinDimension());
  game.render();
  renderer_.Present();
}

SDL2pp::Renderer &Renderer::renderer() {
  return renderer_;
}

int Renderer::getMinDimension() const {
  return std::min(renderer_.GetOutputWidth(), renderer_.GetOutputHeight());
}

int Renderer::getWidth() const {
  return renderer_.GetOutputWidth();
}

int Renderer::getHeight() const {
  return renderer_.GetOutputHeight();
}
