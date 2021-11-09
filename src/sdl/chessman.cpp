#include "chessman.h"

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

void Chessman::drawAt(int x_pos, int y_pos) {
  x_pos -= 4;
  y_pos -= 3;
  x_pos *= width;
  y_pos *= -height;
  sprite.render(x + x_pos, y + y_pos, width, height);
}

Chessman::~Chessman() = default;
