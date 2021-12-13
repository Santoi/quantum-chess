#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_SPRITE_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_SPRITE_REPOSITORY_H

#include <map>
#include "../texture_sprite.h"

class ChessmanSpriteRepository {
  std::map<std::string, TextureSprite> chessmen;
  std::map<std::string, TextureSprite> fills;

  // Load all probability sprites
  void loadFills(Renderer &renderer);

  // Load all chessmen sprites
  void loadChessmen(Renderer &renderer);

public:
  explicit ChessmanSpriteRepository(Renderer &renderer);

  // Get the chessman sprite matched to string
  TextureSprite &getChessman(const std::string &string);

  // Get the probability sprite matched to string
  TextureSprite &getFill(const std::string &string);
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_SPRITE_REPOSITORY_H
