#ifndef QUANTUM_CHESS_PROJ_BUTTON_SPRITE_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_BUTTON_SPRITE_REPOSITORY_H

#include "../texture_sprite.h"
#include <map>

class ButtonSpriteRepository {
  std::map<std::string, TextureSprite> pressed;
  std::map<std::string, TextureSprite> released;

  // Load all pressed button sprites
  void loadPressed(Renderer &renderer);

  // Load all released button sprites
  void loadReleased(Renderer &renderer);

public:
  explicit ButtonSpriteRepository(Renderer &renderer);

  // Get the sprite matched to string
  TextureSprite &getPressed(const std::string &string);

  // Get the sprite matched to string
  TextureSprite &getReleased(const std::string &string);
};


#endif //QUANTUM_CHESS_PROJ_BUTTON_SPRITE_REPOSITORY_H
