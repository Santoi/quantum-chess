#include "button_sprite_repository.h"

#ifndef QCHESS_PATH
#define QCHESS_PATH ""
#endif
#define BUTTONS_PATH "resources/sprites/button/"

ButtonSpriteRepository::ButtonSpriteRepository(Renderer &renderer)
        : pressed(), released() {
  loadPressed(renderer);
  loadReleased(renderer);
}

void ButtonSpriteRepository::loadPressed(Renderer &renderer) {
  std::map<std::string, std::string> images = {
          {"text",             QCHESS_PATH BUTTONS_PATH "text-button-pressed.png"},
          {"action",           QCHESS_PATH BUTTONS_PATH "button-pressed.png"},
          {"match",            QCHESS_PATH BUTTONS_PATH "button-pressed.png"},
          {"role_white",       QCHESS_PATH BUTTONS_PATH "available_white_role.png"},
          {"role_black",       QCHESS_PATH BUTTONS_PATH "available_black_role.png"},
          {"role_spectator",   QCHESS_PATH BUTTONS_PATH "spectator_role.png"},
          {"unavailable_role", QCHESS_PATH BUTTONS_PATH "unavailable_role_layer.png"}
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
          {"text",             QCHESS_PATH BUTTONS_PATH "text-button-released.png"},
          {"action",           QCHESS_PATH BUTTONS_PATH "button-released.png"},
          {"match",            QCHESS_PATH BUTTONS_PATH "button-released.png"},
          {"role_white",       QCHESS_PATH BUTTONS_PATH "available_white_role.png"},
          {"role_black",       QCHESS_PATH BUTTONS_PATH "available_black_role.png"},
          {"role_spectator",   QCHESS_PATH BUTTONS_PATH "spectator_role.png"},
          {"unavailable_role", QCHESS_PATH BUTTONS_PATH "unavailable_role_layer.png"}
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
