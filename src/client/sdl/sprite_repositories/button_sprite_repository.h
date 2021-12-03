#ifndef QUANTUM_CHESS_PROJ_BUTTON_SPRITE_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_BUTTON_SPRITE_REPOSITORY_H

#include "../texture_sprite.h"
#include <map>

class ButtonSpriteRepository {
  std::map<std::string, TextureSprite> pressed;
  std::map<std::string, TextureSprite> released;

  void loadPressed(Renderer &renderer);

  void loadReleased(Renderer &renderer);

public:
  explicit ButtonSpriteRepository(Renderer &renderer);

  TextureSprite &getPressed(const std::string &string);

  TextureSprite &getReleased(const std::string &string);
};


#endif //QUANTUM_CHESS_PROJ_BUTTON_SPRITE_REPOSITORY_H
