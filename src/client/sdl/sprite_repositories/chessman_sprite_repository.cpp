#include "chessman_sprite_repository.h"
#include "../texture_sprite.h"
#include <map>
#include <string>

#define CHESSMAN_PATH "resources/sprites/chessman/"

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
          {"tb", CHESSMAN_PATH "black_tower_quantum.png"},
          {"tw", CHESSMAN_PATH "white_tower_quantum.png"},
          {"hb", CHESSMAN_PATH "black_knight_quantum.png"},
          {"hw", CHESSMAN_PATH "white_knight_quantum.png"},
          {"bb", CHESSMAN_PATH "black_bishop_quantum.png"},
          {"bw", CHESSMAN_PATH "white_bishop_quantum.png"},
          {"kb", CHESSMAN_PATH "black_king_quantum.png"},
          {"kw", CHESSMAN_PATH "white_king_quantum.png"},
          {"qb", CHESSMAN_PATH "black_queen_quantum.png"},
          {"qw", CHESSMAN_PATH "white_queen_quantum.png"},
          {"pb", CHESSMAN_PATH "black_pawn_quantum.png"},
          {"pw", CHESSMAN_PATH "white_pawn_quantum.png"}
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
          {"tb", CHESSMAN_PATH "black_tower.png"},
          {"tw", CHESSMAN_PATH "white_tower.png"},
          {"hb", CHESSMAN_PATH "black_knight.png"},
          {"hw", CHESSMAN_PATH "white_knight.png"},
          {"bb", CHESSMAN_PATH "black_bishop.png"},
          {"bw", CHESSMAN_PATH "white_bishop.png"},
          {"kb", CHESSMAN_PATH "black_king.png"},
          {"kw", CHESSMAN_PATH "white_king.png"},
          {"qb", CHESSMAN_PATH "black_queen.png"},
          {"qw", CHESSMAN_PATH "white_queen.png"},
          {"pb", CHESSMAN_PATH "black_pawn.png"},
          {"pw", CHESSMAN_PATH "white_pawn.png"}
  };
  for (auto &pair: images) {
    TextureSprite chessman(renderer, pair.second,
                           renderer.getMinDimension() / 10,
                           renderer.getMinDimension() / 10);
    chessmen.insert(std::make_pair(pair.first, std::move(chessman)));
  }
}
