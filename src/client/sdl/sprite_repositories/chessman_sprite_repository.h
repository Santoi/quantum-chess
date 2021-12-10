#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_SPRITE_REPOSITORY_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_SPRITE_REPOSITORY_H

#include <map>
#include "../texture_sprite.h"

class ChessmanSpriteRepository {
  std::map<std::string, TextureSprite> chessmen;
  std::map<std::string, TextureSprite> fills;

  void loadFills(Renderer &renderer);

  void loadChessmen(Renderer &renderer);

public:
  explicit ChessmanSpriteRepository(Renderer &renderer);

  TextureSprite &getChessman(const std::string &string);

  TextureSprite &getFill(const std::string &string);
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_SPRITE_REPOSITORY_H
