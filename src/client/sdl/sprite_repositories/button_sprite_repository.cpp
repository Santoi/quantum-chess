#include "button_sprite_repository.h"

ButtonSpriteRepository::ButtonSpriteRepository(Renderer &renderer)
    : pressed(), released() {
  loadPressed(renderer);
  loadReleased(renderer);
}

void ButtonSpriteRepository::loadPressed(Renderer &renderer) {
  std::map<std::string, std::string> images = {
      {"text",             "img/buttons/text-button-pressed.png"},
      {"action",           "img/buttons/button-pressed.png"},
      {"match",            "img/buttons/button-pressed.png"},
      {"role_white",       "img/buttons/available_white_role.png"},
      {"role_black",       "img/buttons/available_black_role.png"},
      {"role_spectator",   "img/buttons/spectator_role.png"},
      {"unavailable_role", "img/buttons/unavailable_role_layer.png"}
  };
  for (auto &pair: images) {
    TextureSprite pressed_(renderer, pair.second,
                           renderer.getWidth() / 4,
                           renderer.getWidth() / 20);
    pressed.insert(std::make_pair(pair.first, std::move(pressed_)));
  }
}

void ButtonSpriteRepository::loadReleased(Renderer &renderer) {
  std::map<std::string, std::string> images = {
      {"text",             "img/buttons/text-button-released.png"},
      {"action",           "img/buttons/button-released.png"},
      {"match",            "img/buttons/button-released.png"},
      {"role_white",       "img/buttons/available_white_role.png"},
      {"role_black",       "img/buttons/available_black_role.png"},
      {"role_spectator",   "img/buttons/spectator_role.png"},
      {"unavailable_role", "img/buttons/unavailable_role_layer.png"}
  };
  for (auto &pair: images) {
    TextureSprite released_(renderer, pair.second,
                            renderer.getWidth() / 4,
                            renderer.getWidth() / 20);
    released.insert(std::make_pair(pair.first, std::move(released_)));
  }
}

TextureSprite &ButtonSpriteRepository::getPressed(const std::string &string) {
  return pressed.at(string);
}

TextureSprite &ButtonSpriteRepository::getReleased(const std::string &string) {
  return released.at(string);
}
