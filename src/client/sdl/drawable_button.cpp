#include "drawable_button.h"

DrawableButton::DrawableButton(Renderer& renderer_, const std::string& not_pressed_file_name,
                               const std::string& pressed_file_name)
                :renderer(renderer_), is_pressed(false), x(0), y(0),
                 height(0), width(0) {
    sprites.reserve(2);
    TextureSprite not_pressed_sprite(renderer_, not_pressed_file_name);
    sprites.push_back(std::move(not_pressed_sprite));
    TextureSprite pressed_sprite(renderer_, pressed_file_name);
    sprites.push_back(std::move(pressed_sprite));
}

DrawableButton::DrawableButton(Renderer& renderer_)
                :renderer(renderer_) {
}

void DrawableButton::render() {
    if (is_pressed)
        sprites[1].render(x, y, width, height);
    else
        sprites[0].render(x, y, width, height);
}

void DrawableButton::changeNotPressedImage(const std::string& not_pressed_file_name) {
    TextureSprite aux_texture_sprite(renderer, not_pressed_file_name);
    sprites[0] = std::move(aux_texture_sprite);
}

void DrawableButton::changePressedImage(const std::string& pressed_file_name) {
    TextureSprite aux_texture_sprite(renderer, pressed_file_name);
    sprites[1] = std::move(aux_texture_sprite);
}

void DrawableButton::setAreaAndPosition(int x_, int y_, int height_, int width_) {
    x = x_;
    y = y_;
    height = height_;
    width = width_;
}

bool DrawableButton::pixelIsOnButton(const PixelCoordinate &pixel_) {
    is_pressed = (pixel_.x() > (unsigned)(x) && pixel_.x() < (unsigned)(x + width) &&
                  pixel_.y() > (unsigned)(y) && pixel_.y() < (unsigned)(y + height));
    return is_pressed;
}

void DrawableButton::disablePressedStatus() {
    is_pressed = false;
}

