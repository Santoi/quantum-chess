#include "button.h"
#include "drawable_button.h"
#include <iostream>

Button::Button(Renderer& renderer_, const std::string& not_pressed_file_name,
               const std::string& pressed_file_name)
        :drawable(renderer_, not_pressed_file_name, pressed_file_name) {
}

Button::Button(Renderer& renderer_)
        :drawable(renderer_) {
}


void Button::render() {
    drawable.render();
}

void Button::setAreaAndPosition(int x_, int y_, int height_, int width_) {
    drawable.setAreaAndPosition(x_, y_, height_, width_);
}

void Button::resetButton() {
    drawable.disablePressedStatus();
}

ConnectButton::ConnectButton(Renderer& renderer,
                             const std::vector<std::unique_ptr<TextEntryButton>>& text_entry_buttons_ptr)
                :Button(renderer, "img/buttons/not_pressed1.png",
                        "img/buttons/pressed.png"),
                 text_entries(text_entry_buttons_ptr) {
}

bool ConnectButton::fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) {
    if (drawable.pixelIsOnButton(pixel_)) {
        std::cout << "button pressed!!" <<std::endl;
        std::vector<std::unique_ptr<TextEntryButton>>::const_iterator it;
        for (it = text_entries.begin(); it != text_entries.end(); it++)
            tokens.push_back((*it)->getText());
        return true;
    }
    std::cout << "button not pressed" <<std::endl;
    return false;
}

PickMatchButton::PickMatchButton(Renderer& renderer, int match_number_, std::vector<ClientData>&& clients_)
                :Button(renderer, "img/buttons/not_pressed_match_button.png",
                        "img/buttons/pressed_match_button.png"),
                        match_number(match_number_), clients(clients_) {
    //Drawable aux(renderer, )
    //drawable =
}

bool PickMatchButton::fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) {
    if (drawable.pixelIsOnButton(pixel_)) {
        std::cout << "match button pressed!!" <<std::endl;
        std::vector<std::unique_ptr<TextEntryButton>>::const_iterator it;
        std::string str_match_number = std::to_string(match_number);
        tokens.push_back(std::move(str_match_number));
        return true;
    }
    std::cout << "button not pressed" <<std::endl;
    return false;
}

RoleButton::RoleButton(Renderer& renderer_, ClientData::Role role_)
            :Button(renderer_), role(role_) {
    if (role_ == ClientData::ROLE_WHITE) {
        drawable.changeNotPressedImage("img/buttons/not_pressed_match_button.png");
        drawable.changePressedImage("img/buttons/pressed_match_button.png");
    } else if (role == ClientData::ROLE_BLACK) {
        drawable.changeNotPressedImage("img/buttons/not_pressed_match_button.png");
        drawable.changePressedImage("img/buttons/pressed_match_button.png");
    } else {
        drawable.changeNotPressedImage("img/buttons/not_pressed_match_button.png");
        drawable.changePressedImage("img/buttons/pressed_match_button.png");
    }
}

bool RoleButton::fillTokensIfClicked(const PixelCoordinate& pixel_, std::list<std::string>& tokens) {
    return false;
}