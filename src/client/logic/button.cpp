#include "button.h"
#include "../sdl/drawables/drawable_button.h"
#include "../../common/client_data.h"
#include <iostream>
#include <string>
#include <list>
#include <vector>

Button::Button(ButtonSpriteRepository &button_repository,
               TextSpriteRepository &text_repository, std::string &&type,
               std::string &&text)
    : drawable(button_repository, text_repository, std::move(type),
               std::move(text)) {
}

void Button::render() {
  drawable.render();
}

void
Button::setAreaAndPosition(size_t x, size_t y, size_t width, size_t height) {
  drawable.setAreaAndPosition(x, y, width, height);
}

void Button::resetButtonToNotPressedState() {
  drawable.disablePressedStatus();
}

ConnectButton::ConnectButton(ButtonSpriteRepository &button_repository,
                             TextSpriteRepository &text_repository,
                             std::string &&button_text,
                             const std::vector<std::unique_ptr<TextEntryButton>>
                             &text_entry_buttons) :
    Button(button_repository, text_repository, "action",
           std::move(button_text)),
    text_entries_ptr(text_entry_buttons) {}

bool ConnectButton::fillTokensIfClicked(const PixelCoordinate &pixel_,
                                        std::list<std::string> &tokens) {
  if (drawable.isPixelOnButton(pixel_)) {
    for (const auto &text_entry: text_entries_ptr)
      tokens.push_back((*text_entry).getText());
    return true;
  }
  return false;
}

PickMatchButton::PickMatchButton(ButtonSpriteRepository &button_repository,
                                 TextSpriteRepository &text_repository,
                                 std::vector<ClientData> &client_data,
                                 uint16_t match_id)
    : Button(button_repository, text_repository, "match", ""),
      match_id(match_id) {
  std::string match_info = "#" + std::to_string(match_id) + ": ";
  std::string client_info;
  for (auto it = client_data.begin(); it != client_data.end(); ++it) {
    char role;
    switch (it->role) {
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
    client_info += it->name + "#" + std::to_string(it->id) + "("
                   + role + "), ";
  }
  if (client_info.empty()) {
    match_info = "NEW GAME";
  } else {
    match_info += client_info;
    match_info[-2] = '\0'; // remove the last comma
  }
  drawable.setText(std::move(match_info), 'k');
}

bool PickMatchButton::fillTokensIfClicked(const PixelCoordinate &pixel_,
                                          std::list<std::string> &tokens) {
  if (drawable.isPixelOnButton(pixel_)) {
    std::string str_match_number = std::to_string(match_id);
    tokens.push_back(std::move(str_match_number));
    return true;
  }
  return false;
}

NextMatchesButton::NextMatchesButton(
    ButtonSpriteRepository &button_repository,
    TextSpriteRepository &text_repository) : Button(button_repository,
                                                    text_repository, "action",
                                                    "") {
  drawable.setText("NEXT", 'k');
}

bool NextMatchesButton::fillTokensIfClicked(const PixelCoordinate &pixel_,
                                            std::list<std::string> &tokens) {
  bool clicked = drawable.isPixelOnButton(pixel_);
  if (clicked)
    tokens.emplace_back("NEXT");
  return clicked;
}

PreviousMatchesButton::PreviousMatchesButton(
    ButtonSpriteRepository &button_repository,
    TextSpriteRepository &text_repository) : Button(button_repository,
                                                    text_repository, "action",
                                                    "") {
  drawable.setText("PREV", 'k');
}

bool
PreviousMatchesButton::fillTokensIfClicked(const PixelCoordinate &pixel_,
                                           std::list<std::string> &tokens) {
  bool clicked = drawable.isPixelOnButton(pixel_);
  if (clicked)
    tokens.emplace_back("PREV");
  return clicked;
}

RefreshMatchesButton::RefreshMatchesButton(
    ButtonSpriteRepository &button_repository,
    TextSpriteRepository &text_repository) : Button(button_repository,
                                                    text_repository, "action",
                                                    "") {
  drawable.setText("REFRESH", 'k');
}

bool RefreshMatchesButton::fillTokensIfClicked(const PixelCoordinate &pixel_,
                                               std::list<std::string> &tokens) {
  bool clicked = drawable.isPixelOnButton(pixel_);
  if (clicked) {
    std::string refresh_signal = std::to_string(UINT16_MAX);
    tokens.emplace_back(std::move(refresh_signal));
  }
  return clicked;
}

RoleButton::RoleButton(ButtonSpriteRepository &button_repository,
                       TextSpriteRepository &text_repository,
                       ClientData::Role role_, std::string &&type,
                       bool role_is_available_)
    : Button(button_repository, text_repository, std::move(type), ""),
      role(role_), unavailable_role_sprite(
        &button_repository.getPressed("unavailable_role")),
      role_is_available(role_is_available_) {
}

void RoleButton::render() {
  Button::render();
  if (!role_is_available) {
    size_t x, y, width, height;
    drawable.getAreaAndPosition(x, y, width, height);
    unavailable_role_sprite->render(x, y, width, height);
  }
}

void RoleButton::addEnumToListOfTokens(std::list<std::string> &tokens) {
  if (role == ClientData::ROLE_WHITE)
    tokens.emplace_back("ROLE_WHITE");
  else if (role == ClientData::ROLE_BLACK)
    tokens.emplace_back("ROLE_BLACK");
  else
    tokens.emplace_back("ROLE_SPECTATOR");
}


bool RoleButton::fillTokensIfClicked(const PixelCoordinate &pixel_,
                                     std::list<std::string> &tokens) {
  if (drawable.isPixelOnButton(pixel_)) {
    if (role_is_available)
      addEnumToListOfTokens(tokens);
    return true;
  }
  return false;
}
