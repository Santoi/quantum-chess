#include "chessman.h"
#include <iostream>
#include <utility>

Chessman::Chessman(Renderer &renderer, const std::string &chessman,
                   int probability_): renderer(renderer),
                   sprite_(renderer, "img/falcon.png",
                           renderer.getMinDimension() / 10,
                           renderer.getMinDimension() / 10),
                   fill(renderer, "img/falcon.png",
                           renderer.getMinDimension() / 10,
                           renderer.getMinDimension() / 10),
                   probability(probability_ / 100.0f) {
  image = {
    {"tb", std::make_pair<std::string, std::string>
      ("img/black_tower_quantum.png", "img/black_tower.png")},
    {"tw", std::make_pair<std::string, std::string>
      ("img/white_tower_quantum.png", "img/white_tower.png")},
    {"kb", std::make_pair<std::string, std::string>
      ("img/black_knight_quantum.png", "img/black_knight.png")},
    {"kw", std::make_pair<std::string, std::string>
      ("img/white_knight_quantum.png", "img/white_knight.png")},
    {"bb", std::make_pair<std::string, std::string>
      ("img/black_bishop_quantum.png", "img/black_bishop.png")},
    {"bw", std::make_pair<std::string, std::string>
      ("img/white_bishop_quantum.png", "img/white_bishop.png")},
    {"Kb", std::make_pair<std::string, std::string>
      ("img/black_king_quantum.png", "img/black_king.png")},
    {"Kw", std::make_pair<std::string, std::string>
      ("img/white_king_quantum.png", "img/white_king.png")},
    {"qb", std::make_pair<std::string, std::string>
      ("img/black_queen_quantum.png", "img/black_queen.png")},
    {"qw", std::make_pair<std::string, std::string>
      ("img/white_queen_quantum.png", "img/white_queen.png")},
    {"pb", std::make_pair<std::string, std::string>
      ("img/black_pawn_quantum.png", "img/black_pawn.png")},
    {"pw", std::make_pair<std::string, std::string>
      ("img/white_pawn_quantum.png", "img/white_pawn.png")},
  };
  fill.loadImage(image[chessman].first, renderer.getMinDimension() / 10,
                 renderer.getMinDimension() / 10);
  sprite_.loadImage(image[chessman].second, renderer.getMinDimension() / 10,
                    renderer.getMinDimension() / 10);
}

Chessman::Chessman(Chessman &&other) noexcept: renderer(other.renderer),
                                      sprite_(std::move(other.sprite_)),
                                      fill(std::move(other.fill)),
                                      image(std::move(other.image)),
                                      probability(other.probability) {}

Chessman& Chessman::operator=(Chessman &&other) noexcept {
  renderer = std::move(other.renderer);
  sprite_ = std::move(other.sprite_);
  image = std::move(other.image);
  probability = other.probability;
  return *this;
}

void Chessman::render(int x, int y) {
  int size = renderer.getMinDimension() / 10;
  int dy = size - size * probability;
  fill.render(0, dy, x, y + dy, size, size * probability, size, size);
  sprite_.render(x, y, size, size);
}

Chessman::~Chessman() = default;
