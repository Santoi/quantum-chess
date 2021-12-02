#ifndef QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
#define QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H

#include "texture_sprite.h"
#include <vector>
#include "pixel_coordinate.h"

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

    DrawableButton(Renderer& renderer_, const std::string& not_pressed_file_name,
                   const std::string& pressed_file_name);

    DrawableButton(Renderer& renderer_);

    void render();

    void changeNotPressedImage(const std::string& not_pressed_file_name);

    void changePressedImage(const std::string& pressed_file_name);

    bool pixelIsOnButton(const PixelCoordinate& pixel_);

    void setAreaAndPosition(int x, int y, int height, int width);

    void disablePressedStatus();

    ~DrawableButton() = default;
};

#endif //QUANTUM_CHESS_PROJ_DRAWABLE_BUTTON_H
