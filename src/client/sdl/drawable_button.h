#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H

#include "texture_sprite.h"
#include <vector>

class Renderer;

class DrawableButton {
private:
    Renderer& renderer;
    std::vector<TextureSprite> sprites;
    bool is_pressed;
    int x;
    int y;
    int height;
    int width;

public:

    DrawableButton() = delete;

    DrawableButton(Renderer& renderer_, const std::string& not_pressed_file_name,
                   const std::string& pressed_file_name);

    void render();

    void setAreaAndPosition(int x, int y, int height, int width);

    ~DrawableButton() = default;
};

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
