#include "text_entry_button.h"

TextEntryButton::TextEntryButton(const std::string& button_name_)
                :button_name(button_name_), x(0), y(0), width(0), height(0), expecting_text(false) {
}

void TextEntryButton::setAreaAndPosition(int x_, int y_, int height_, int width_) {
    x = x_;
    y = y_;
    height = height_;
    width = width_;
}

void TextEntryButton::setScale(const int& scale_) {
    scale = scale_;
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
