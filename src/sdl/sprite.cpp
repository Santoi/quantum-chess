#include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>
#include <string>

Sprite::Sprite(SDL2pp::Renderer &renderer, const std::string
               &file_name) : renderer(renderer), sprite(renderer, file_name) {}

Sprite::Sprite(SDL2pp::Renderer &renderer, const std::string
           &file_name, int width, int height) : renderer(renderer),
                                                sprite(renderer, file_name) {
  renderer.Copy(sprite, SDL2pp::NullOpt,
                                 SDL2pp::Rect(0, 0, width, height));
}

void Sprite::render() {
  renderer.Copy(sprite);
}

void Sprite::render(int x, int y, int width, int height) {
  const SDL2pp::Rect dest(x, y, width, height);
  renderer.Copy(sprite, SDL2pp::NullOpt, dest);
}
void Sprite::loadImage(const std::string &file_name) {
  SDL2pp::Texture new_sprite(renderer, file_name);
  sprite = std::move(new_sprite);
}

Sprite::~Sprite() = default;
