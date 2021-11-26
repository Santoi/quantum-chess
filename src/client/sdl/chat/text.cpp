#include "text.h"
#include "../renderer.h"
#include "text_sprite.h"
#include <string>
#include <iostream>


void Text::concat(const std::string &str) {
  text.append(str);
}

void Text::delete_last() {
  if (!text.empty())
    text.pop_back();
}

void Text::render(int x, int y, int width, int height) {
  if (!text.empty())
    sprite.render(text, x, y, width, height);
}


