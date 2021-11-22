#include "chessman_sprite_repository.h"
#include "../main_drawer.h"

ChessmanSpriteRepository::ChessmanSpriteRepository(Renderer & renderer): chessmen(), fills() {
  loadFills(renderer);
  loadChessmen(renderer);
}

Sprite & ChessmanSpriteRepository::getChessman(const std::string & string){
  return chessmen.at(string);
}

Sprite & ChessmanSpriteRepository::getFill(const std::string & string) {
  return fills.at(string);
}

void ChessmanSpriteRepository::loadFills(Renderer & renderer) {
  std::map<std::string, std::string> images = {
          {"tb", "img/black_tower_quantum.png"},
          {"tw", "img/white_tower_quantum.png"},
          {"hb", "img/black_knight_quantum.png"},
          {"hw", "img/white_knight_quantum.png"},
          {"bb", "img/black_bishop_quantum.png"},
          {"bw", "img/white_bishop_quantum.png"},
          {"kb", "img/black_king_quantum.png"},
          {"kw", "img/white_king_quantum.png"},
          {"qb", "img/black_queen_quantum.png"},
          {"qw", "img/white_queen_quantum.png"},
          {"pb", "img/black_pawn_quantum.png"},
          {"pw", "img/white_pawn_quantum.png"}
  };
  for (auto & pair: images) {
    Sprite fill(renderer, pair.second,
                renderer.getMinDimension() / 10,
                renderer.getMinDimension() / 10);
    fills.insert(std::make_pair(pair.first, std::move(fill)));
  }
}

void ChessmanSpriteRepository::loadChessmen(Renderer &renderer) {
  std::map<std::string, std::string> images = {
          {"tb", "img/black_tower.png"},
          {"tw", "img/white_tower.png"},
          {"hb", "img/black_knight.png"},
          {"hw", "img/white_knight.png"},
          {"bb", "img/black_bishop.png"},
          {"bw", "img/white_bishop.png"},
          {"kb", "img/black_king.png"},
          {"kw", "img/white_king.png"},
          {"qb", "img/black_queen.png"},
          {"qw", "img/white_queen.png"},
          {"pb", "img/black_pawn.png"},
          {"pw", "img/white_pawn.png"}
  };
  for (auto & pair: images) {
    Sprite chessman(renderer, pair.second,
                    renderer.getMinDimension() / 10,
                    renderer.getMinDimension() / 10);
    chessmen.insert(std::make_pair(pair.first, std::move(chessman)));
  }
}