#include "text_entry_button.h"

TextEntryButton::TextEntryButton(Renderer& renderer_, const std::string& button_name_)
                :button_name(button_name_), text_texture(renderer_, "img/buttons/White_text_field.png"),
                 name_texture(renderer_, "img/buttons/ip_text.png"),
                 x(0), y(0), width(0), height(0), expecting_text(false) {
}

void TextEntryButton::setAreaAndPosition(int x_, int y_, int height_, int width_) {
    x = x_;
    y = y_;
    height = height_;
    width = width_;
}

void TextEntryButton::render() {
    text_texture.render(x + 60, y, width - 60, height);
    name_texture.render(x, y, 40, height);
}

bool TextEntryButton::enableTextEntryIfClicked(const PixelCoordinate& pixel) {
    //if (pixel is in area)
    //  expecting_text = true;
    //enable text entry if clicked. return true in this case
    //else return false
    return false;
}

void TextEntryButton::disableTextEntry() {
    expecting_text = false;
}

std::string TextEntryButton::getText() const {
    //get string from text entry
    std::string current_text;
    return current_text;
}
