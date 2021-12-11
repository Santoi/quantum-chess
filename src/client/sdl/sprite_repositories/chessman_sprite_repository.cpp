#include "chessman_sprite_repository.h"
#include "../texture_sprite.h"

#ifndef QCHESS_PATH
#define QCHESS_PATH ""
#endif
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
          {"tb", QCHESS_PATH CHESSMAN_PATH "black_tower_quantum.png"},
          {"tw", QCHESS_PATH CHESSMAN_PATH "white_tower_quantum.png"},
          {"hb", QCHESS_PATH CHESSMAN_PATH "black_knight_quantum.png"},
          {"hw", QCHESS_PATH CHESSMAN_PATH "white_knight_quantum.png"},
          {"bb", QCHESS_PATH CHESSMAN_PATH "black_bishop_quantum.png"},
          {"bw", QCHESS_PATH CHESSMAN_PATH "white_bishop_quantum.png"},
          {"kb", QCHESS_PATH CHESSMAN_PATH "black_king_quantum.png"},
          {"kw", QCHESS_PATH CHESSMAN_PATH "white_king_quantum.png"},
          {"qb", QCHESS_PATH CHESSMAN_PATH "black_queen_quantum.png"},
          {"qw", QCHESS_PATH CHESSMAN_PATH "white_queen_quantum.png"},
          {"pb", QCHESS_PATH CHESSMAN_PATH "black_pawn_quantum.png"},
          {"pw", QCHESS_PATH CHESSMAN_PATH "white_pawn_quantum.png"}
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
          {"tb", QCHESS_PATH CHESSMAN_PATH "black_tower.png"},
          {"tw", QCHESS_PATH CHESSMAN_PATH "white_tower.png"},
          {"hb", QCHESS_PATH CHESSMAN_PATH "black_knight.png"},
          {"hw", QCHESS_PATH CHESSMAN_PATH "white_knight.png"},
          {"bb", QCHESS_PATH CHESSMAN_PATH "black_bishop.png"},
          {"bw", QCHESS_PATH CHESSMAN_PATH "white_bishop.png"},
          {"kb", QCHESS_PATH CHESSMAN_PATH "black_king.png"},
          {"kw", QCHESS_PATH CHESSMAN_PATH "white_king.png"},
          {"qb", QCHESS_PATH CHESSMAN_PATH "black_queen.png"},
          {"qw", QCHESS_PATH CHESSMAN_PATH "white_queen.png"},
          {"pb", QCHESS_PATH CHESSMAN_PATH "black_pawn.png"},
          {"pw", QCHESS_PATH CHESSMAN_PATH "white_pawn.png"}
  };
  for (auto &pair: images) {
    TextureSprite chessman(renderer, pair.second,
                           renderer.getMinDimension() / 10,
                           renderer.getMinDimension() / 10);
    chessmen.insert(std::make_pair(pair.first, std::move(chessman)));
  }
}
