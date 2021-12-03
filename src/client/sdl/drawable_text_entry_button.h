#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_ENTRY_BUTTON_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_ENTRY_BUTTON_H

#include "pixel_coordinate.h"
#include "chat/font.h"
#include "chat/drawable_text.h"
#include "texture_sprite.h"
#include "chat/drawable_container.h"
#include <string>

class Renderer;

class DrawableTextEntryButton {
private:
    Renderer& renderer;
    TextSpriteRepository &repository;
    const std::string button_name;
    TextureSprite text_box;
    DrawableText text_entry;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;

public:

    DrawableTextEntryButton() = delete;

    DrawableTextEntryButton(Renderer& renderer, TextSpriteRepository
    &repository, const std::string &default_text);

    void setAreaAndPosition(int x_, int y_, int height_, int width_);

    bool pixelIsOnTextEntry(const PixelCoordinate& pixel) const;

    void render(const std::string& current_text);
};

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_TEXT_ENTRY_BUTTON_H
