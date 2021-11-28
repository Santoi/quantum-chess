#include "renderer.h"
#include "sprite.h"

Sprite::Sprite(Renderer
               &renderer,
               const std::string &file_name,
               int width,
               int height
) :

    renderer(
        renderer), sprite_(renderer.renderer(), file_name), width_(width),
    height_(height) {}

Sprite::Sprite(Renderer
               &renderer,
               const SDL2pp::Surface &surface,
               int width,
               int height
) :

    renderer(renderer),
    sprite_(renderer.renderer(),
            surface),
    width_(width), height_(height) {}

int Sprite::width() const {
  return width_;
}

int Sprite::height() const {
  return height_;
}

SDL2pp::Texture &Sprite::sprite() {
  return sprite_;
}
