#include "chessman.h"
#include <utility>

Chessman::Chessman(SDL2pp::Renderer &renderer, char chessman) :
                                    renderer(renderer),
                                    sprite(renderer, "img/falcon.png") {
  x = y = renderer.GetOutputHeight() / 2;
  width = height = renderer.GetOutputHeight() / 10;

  switch (chessman) {
    case 't':
      sprite.loadImage("img/tower.png");
      break;
    case 'b':
      sprite.loadImage("img/bishop.png");
      break;
    default:
      break;
  }
}

void Chessman::move(int x_pos, int y_pos) {
  updateDimensions();
  x_pos -= 4;
  y_pos -= 3;
  x_pos *= width;
  y_pos *= -height;
  sprite.render(x + x_pos, y + y_pos, width, height);
}

void Chessman::updateDimensions() {
  x = y = std::min(renderer.GetOutputHeight(), renderer.GetOutputWidth()) / 2;
  width = height = std::min(renderer.GetOutputHeight(),
                            renderer.GetOutputWidth()) / 10;
}

Chessman::~Chessman() = default;
