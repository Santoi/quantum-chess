#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_ENTRY_BUTTON_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_ENTRY_BUTTON_H

#include "pixel_coordinate.h"
#include "chat/font.h"
#include "chat/drawable_text.h"
#include <string>

class Renderer;

class DrawableTextEntryButton {
private:
    Renderer& renderer;
    const std::string button_name;
    TextureSprite text_texture;
    TextureSprite name_texture;
    int x;
    int y;
    int width;
    int height;

public:

    DrawableTextEntryButton() = delete;

    DrawableTextEntryButton(Renderer& renderer_, const std::string& button_name_)
                            :renderer(renderer_), button_name(button_name_),
                             text_texture(renderer_, "img/buttons/White_text_field.png"),
                             name_texture(renderer_, button_name_), x(0), y(0), width(0),
                             height(0)  {
    }

    void setAreaAndPosition(int x_, int y_, int height_, int width_) {
        x = x_;
        y = y_;
        height = height_;
        width = width_;
    }

    bool pixelIsOnTextEntry(const PixelCoordinate& pixel_) {
        return (pixel_.x() > (unsigned)(x) && pixel_.x() < (unsigned)(x + width) &&
                pixel_.y() > (unsigned)(y) && pixel_.y() < (unsigned)(y + height));
    }

    void render(const std::string& current_text) {
         text_texture.render(x + 60, y, width - 60, height);
         name_texture.render(x, y, 40, height);
         if (current_text.empty())
             return;
         Font font(10);
         DrawableText drawable_text(renderer, font, current_text, 'k');
         drawable_text.render(x + 65, y);
    }
};

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_ENTRY_BUTTON_H
