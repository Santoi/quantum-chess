#include "button.h"
#include "drawable_button.h"
#include <iostream>

Button::Button(Renderer& renderer_, const std::string& not_pressed_file_name,
               const std::string& pressed_file_name)
        :drawable(renderer_, not_pressed_file_name, pressed_file_name) {
}

void Button::render() {
    drawable.render();
}

void Button::setScale(const int& scale_) {
    drawable.setScale(scale_);
}


void Button::setAreaAndPosition(int x_, int y_, int height_, int width_) {
    drawable.setAreaAndPosition(x_, y_, height_, width_);
}


ConnectButton::ConnectButton(Renderer& renderer,
                             const std::vector<std::unique_ptr<TextEntryButton>>& text_entry_buttons_ptr)
                :Button(renderer, "img/buttons/not_pressed_connect_button.png",
                        "img/buttons/pressed_connect_button.png"),
                 text_entries(text_entry_buttons_ptr) {
}

bool ConnectButton::fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) {
    if (drawable.pixelIsOnButton(pixel_)) {
        std::cout << "button pressed!!" <<std::endl;
        std::vector<std::unique_ptr<TextEntryButton>>::const_iterator it;
        for (it = text_entries.begin(); it != text_entries.end(); it++)
            tokens.push_back((*it)->getText());
        return true;
    } else {
        std::cout << "button not pressed" <<std::endl;
        return false;
    }
}

bool PickMatchButton::fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) {
    return false;
}