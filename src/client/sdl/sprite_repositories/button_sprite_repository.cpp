#include "button_sprite_repository.h"

#define PATH "resources/sprites/button/"
#define PATH_IMAGES "resources/sprites/"
ButtonSpriteRepository::ButtonSpriteRepository(Renderer &renderer)
    : pressed(), released() {
  loadPressed(renderer);
  loadReleased(renderer);
}

void ButtonSpriteRepository::loadPressed(Renderer &renderer) {
  std::map<std::string, std::string> images = {
      {"text",             PATH "text-button-pressed.png"},
      {"action",           PATH "button-pressed.png"},
      {"match",            PATH "button-pressed.png"},
      {"role_white",       PATH "available_white_role.png"},
      {"role_black",       PATH "available_black_role.png"},
      {"role_spectator",   PATH "spectator_role.png"},
      {"unavailable_role", PATH "unavailable_role_layer.png"},
      {"return", PATH "return.png"},
      {"help", PATH_IMAGES "help_image.png"},
      {"leave", PATH_IMAGES "leave_match_question.png"},
      {"coronation", PATH_IMAGES "coronation_image.png"}
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
      {"text",             PATH "text-button-released.png"},
      {"action",           PATH "button-released.png"},
      {"match",            PATH "button-released.png"},
      {"role_white",       PATH "available_white_role.png"},
      {"role_black",       PATH "available_black_role.png"},
      {"role_spectator",   PATH "spectator_role.png"},
      {"unavailable_role", PATH "unavailable_role_layer.png"},
      {"return", PATH "return.png"}
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
