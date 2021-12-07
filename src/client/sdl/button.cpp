#include "button.h"
#include "drawable_button.h"
#include "../../common/src/client_data.h"
#include <iostream>

Button::Button(ButtonSpriteRepository &button_repository,
               TextSpriteRepository &text_repository, std::string &&type,
               std::string &&text)
    : drawable(button_repository, text_repository, std::move(type),
               std::move(text)) {
}

void Button::render() {
  drawable.render();
}

void Button::setAreaAndPosition(int x, int y, int width, int height) {
  drawable.setAreaAndPosition(x, y, width, height);
}


ConnectButton::ConnectButton(ButtonSpriteRepository &button_repository,
                             TextSpriteRepository &text_repository,
                             std::string &&button_text,
                             const std::list<TextEntryButton> &text_entry_buttons)
    : Button(button_repository, text_repository, "action",
             std::move(button_text)),
      text_entries(text_entry_buttons) {}

bool ConnectButton::fillTokensIfClicked(const PixelCoordinate &pixel_,
                                        std::list<std::string> &tokens) {
  if (drawable.pixelIsOnButton(pixel_)) {
    std::cout << "button pressed!!" << std::endl;
    for (const auto &text_entry: text_entries)
      tokens.push_back(text_entry.getText());
    return true;
  }
  std::cout << "button not pressed" << std::endl;
  return false;
}

PickMatchButton::PickMatchButton(ButtonSpriteRepository &button_repository,
                                 TextSpriteRepository &text_repository,
                                 std::vector<ClientData> &client_data,
                                 uint16_t match_id)
    : Button(button_repository, text_repository, "match",
             ""),
      match_id(match_id) {
  std::string match_info = "#" + std::to_string(match_id) + ": ";
  for (auto &client: client_data) {
    char role;
    switch (client.role) {
      case ClientData::ROLE_WHITE:
        role = 'w';
        break;
      case ClientData::ROLE_BLACK:
        role = 'b';
        break;
      case ClientData::ROLE_SPECTATOR:
        role = 'o';
        break;
      default:
        role = ' ';
    }
    match_info += client.name + "#" + std::to_string(client.id) + "("
                  + role + "), ";
  }

}

bool PickMatchButton::fillTokensIfClicked(const PixelCoordinate &pixel_,
                                          std::list<std::string> &tokens) {
  if (drawable.pixelIsOnButton(pixel_)) {
    std::cout << "match button pressed!!" << std::endl;
    std::string str_match_number = std::to_string(match_id);
    tokens.push_back(std::move(str_match_number));
    return true;
  }
  std::cout << "button not pressed" << std::endl;
  return false;
}
