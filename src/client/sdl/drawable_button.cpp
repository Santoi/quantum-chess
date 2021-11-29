#include "drawable_button.h"

DrawableButton::DrawableButton(Renderer& renderer_)
                :renderer(renderer_), x(0), y(0), height(0), width(0) {
}

void DrawableButton::render() {
}

void DrawableButton::setAreaAndPosition(int x_, int y_, int height_, int width_) {
    x = x_;
    y = y_;
    height = height_;
    width = width_;
}
