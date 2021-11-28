#include "button.h"

void Button::setAreaAndPosition(int x_, int y_, int height_, int width_) {
    x = x_;
    y = y_;
    height = height_;
    width = width_;
}

ConnectButton::ConnectButton(const std::list<std::unique_ptr<TextEntryButton>>& text_entry_buttons_ptr)
                :text_entries(text_entry_buttons_ptr) {
}

bool ConnectButton::fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) {
    return false;
}

bool PickMatchButton::fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) {
    return false;
}