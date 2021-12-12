#include "chessman_sprite_repository.h"
#include "../texture_sprite.h"

#define PATH "resources/sprites/chessman/"

ChessmanSpriteRepository::ChessmanSpriteRepository(Renderer &renderer)
    : chessmen(), fills() {
  loadFills(renderer);
  loadChessmen(renderer);
}

TextureSprite &
ChessmanSpriteRepository::getChessman(const std::string &string) {
  return chessmen.at(string);
}

TextureSprite &ChessmanSpriteRepository::getFill(const std::string &string) {
  return fills.at(string);
}

void ChessmanSpriteRepository::loadFills(Renderer &renderer) {
  std::map<std::string, std::string> images = {
      {"tb", PATH "black_tower_quantum.png"},
      {"tw", PATH "white_tower_quantum.png"},
      {"hb", PATH "black_knight_quantum.png"},
      {"hw", PATH "white_knight_quantum.png"},
      {"bb", PATH "black_bishop_quantum.png"},
      {"bw", PATH "white_bishop_quantum.png"},
      {"kb", PATH "black_king_quantum.png"},
      {"kw", PATH "white_king_quantum.png"},
      {"qb", PATH "black_queen_quantum.png"},
      {"qw", PATH "white_queen_quantum.png"},
      {"pb", PATH "black_pawn_quantum.png"},
      {"pw", PATH "white_pawn_quantum.png"}
  };
  for (auto &pair: images) {
    TextureSprite fill(renderer, pair.second,
                       renderer.getMinDimension() / 10,
                       renderer.getMinDimension() / 10);
    fills.insert(std::make_pair(pair.first, std::move(fill)));
  }
}

void ChessmanSpriteRepository::loadChessmen(Renderer &renderer) {
  std::map<std::string, std::string> images = {
      {"tb", PATH "black_tower.png"},
      {"tw", PATH "white_tower.png"},
      {"hb", PATH "black_knight.png"},
      {"hw", PATH "white_knight.png"},
      {"bb", PATH "black_bishop.png"},
      {"bw", PATH "white_bishop.png"},
      {"kb", PATH "black_king.png"},
      {"kw", PATH "white_king.png"},
      {"qb", PATH "black_queen.png"},
      {"qw", PATH "white_queen.png"},
      {"pb", PATH "black_pawn.png"},
      {"pw", PATH "white_pawn.png"}
  };
  for (auto &pair: images) {
    TextureSprite chessman(renderer, pair.second,
                           renderer.getMinDimension() / 10,
                           renderer.getMinDimension() / 10);
    chessmen.insert(std::make_pair(pair.first, std::move(chessman)));
  }
}
