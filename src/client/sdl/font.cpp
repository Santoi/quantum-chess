#include "font.h"
#include <string>
#include <list>

#define BLACK {0x00, 0x00, 0x00}
#define WHITE {0xff, 0xff, 0xff}
#define RED {0xff, 0x00, 0x00}
#define GREEN {0x00, 0x80, 0x00}
#define BLUE {0x00, 0x00, 0xff}
#define GRAY {0x80, 0x80, 0x80}
#define YELLOW {0xff, 0xff, 0x00}
#define NAVY {0x00, 0x00, 0x80}
#define FUCHSIA {0xff, 0x00, 0xff}
#define LIME {0x00, 0xff, 0x00}
#define PURPLE {0x80, 0x00, 0x80}
#define TEAL {0x00, 0xff, 0xff}

#define FONTS_PATH "resources/fonts/"

Font::Font(int ptx, int index)
    : ttf(),
      mono_font(FONTS_PATH "erusfont.pcf", ptx, index),
      colors({
                 {'k', BLACK},
                 {'w', WHITE},
                 {'r', RED},
                 {'g', GREEN},
                 {'b', BLUE},
                 {'y', YELLOW},
                 {'n', NAVY},
                 {'f', FUCHSIA},
                 {'l', LIME},
                 {'p', PURPLE},
                 {'d', GRAY},
                 {'t', TEAL},
             }) {}

SDL2pp::Surface Font::renderMonoText(const std::string &text, char color) {
  return mono_font.RenderText_Solid(text, colors[color]);
}

size_t Font::size() const {
  return mono_font.GetHeight();
}

std::list<char> Font::getColors() const {
  std::list<char> color_list;
  for (auto it = colors.begin(); it != colors.end(); ++it) {
    color_list.push_back(it->first);
  }
  return color_list;
}
