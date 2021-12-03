#include "button_sprite_repository.h"

ButtonSpriteRepository::ButtonSpriteRepository(Renderer &renderer): pressed(), released() {
  loadPressed(renderer);
  loadReleased(renderer);
}

void ButtonSpriteRepository::loadPressed(Renderer &renderer) {
  std::map<std::string, std::string> images = {
      {"text", "img/buttons/text_field_pressed.png"},
      {"action", "img/buttons/submit_pressed.png"},
  };
  for (auto &pair: images) {
    TextureSprite pressed_(renderer, pair.second,
                       renderer.getMinDimension() / 4,
                       renderer.getMinDimension() / 20);
    pressed.insert(std::make_pair(pair.first, std::move(pressed_)));
  }
}

void ButtonSpriteRepository::loadReleased(Renderer &renderer) {
  std::map<std::string, std::string> images = {
      {"text", "img/buttons/text_field_released.png"},
      {"action", "img/buttons/submit_released.png"},
  };
  for (auto &pair: images) {
    TextureSprite released_(renderer, pair.second,
                           renderer.getMinDimension() / 4,
                           renderer.getMinDimension() / 20);
    released.insert(std::make_pair(pair.first, std::move(released_)));
  }
}

TextureSprite &ButtonSpriteRepository::getPressed(const std::string &string) {
  return pressed.at(string);
}

TextureSprite &ButtonSpriteRepository::getReleased(const std::string &string) {
  return released.at(string);
}
