#include "login_state.h"
#include "../../common/src/unique_ptr.h"
#include "../../common/src/client_data.h"
#include "unavailable_role_exception.h"
#include <iostream>

LoginState::LoginState(Login &login_,
                       ButtonSpriteRepository &button_sprite_repository,
                       TextSpriteRepository &text_sprite_repository) :
        login(login_),
        button_sprite_repository(button_sprite_repository),
        text_sprite_repository(text_sprite_repository) {}

void LoginState::resetPressedButtons() {
  for (auto &button: button_list)
    button->resetButton();
}

ConnectToServerState::ConnectToServerState(Login &login_,
                                           ButtonSpriteRepository &button_sprite_repository,
                                           TextSpriteRepository &text_sprite_repository)
        : LoginState(login_, button_sprite_repository, text_sprite_repository) {
  text_entry_button_list.emplace_back(button_sprite_repository,
                                      text_sprite_repository, "IP");
  text_entry_button_list.emplace_back(button_sprite_repository,
                                      text_sprite_repository, "PORT");
  button_list.push_back(make_unique<ConnectButton>(button_sprite_repository,
                                                   text_sprite_repository,
                                                   "CONNECT",
                                                   text_entry_button_list));
}

bool ConnectToServerState::clientIsConnectedToMatch() {
  return false;
}

void ConnectToServerState::render(LoginScene &login_scene) {
  login_scene.renderIPAndPortFields(*button_list.front(),
                                    text_entry_button_list.front(),
                                    *(++text_entry_button_list.begin()));
}

void ConnectToServerState::fillWithActiveButtons(
        std::list<std::reference_wrapper<Button>> &active_buttons) {
  for (auto &button: button_list)
    active_buttons.emplace_back(*button);
}

void ConnectToServerState::fillWithActiveTextEntryButtons(
        std::list<std::reference_wrapper<TextEntryButton>> &
        active_text_entries) {
  for (auto &button: text_entry_button_list)
    active_text_entries.emplace_back(button);
}

int ConnectToServerState::processTokens(std::list<std::string> &&tokens) {
  std::string ip = tokens.front(); //tokens strings has the same order as how TextEntryButton are in the list
  //(first the ip string, second the port string)
  tokens.pop_front();
  std::cout << ip << std::endl;
  std::string port = tokens.front();
  tokens.pop_front();
  std::cout << port << std::endl;
  login.connectToServer(ip, port);
  return NEXT_STATE_CONNECT_TO_MATCH;
  //pop port token, ip, name...
  //tell login to connect to socket
}

bool SelectingRoleState::clientIsConnectedToMatch() {
  return false;
}

void
SelectingRoleState::render(LoginScene &login_scene) {
  login_scene.renderRolesButtons(**button_list.begin(),
                                 **(++button_list.begin()),
                                 **button_list.end());
}

void SelectingRoleState::fillWithActiveButtons(
        std::list<std::reference_wrapper<Button>> &active_buttons) {
  for (auto &button: button_list)
    active_buttons.emplace_back(*button);
}

void SelectingRoleState::fillWithActiveTextEntryButtons(
        std::list<std::reference_wrapper<TextEntryButton>> &
        active_text_entries) {}

ClientData::Role
SelectingRoleState::getRoleFromString(const std::string &str_selected_role) {
  // TODO revisar.
  if (str_selected_role == "ROLE_WHITE")
    return ClientData::ROLE_WHITE;
  else if (str_selected_role == "ROLE_BLACK")
    return ClientData::ROLE_BLACK;
  else
    return ClientData::ROLE_SPECTATOR;
}

int SelectingRoleState::processTokens(std::list<std::string> &&tokens) {
  if (tokens.empty())
    throw UnavailableRoleException();
  std::string str_selected_role = tokens.front();
  ClientData::Role selected_role = getRoleFromString(str_selected_role);
  login.sendChosenRole(selected_role);
  return NEXT_STATE_CONNECTED_TO_MATCH;
}

SelectingRoleState::SelectingRoleState(Login &login_,
                                       ButtonSpriteRepository &button_repository,
                                       TextSpriteRepository &text_repository)
        : LoginState(login_, button_repository, text_repository) {}

ConnectToMatchState::ConnectToMatchState(Login &login_,
                                         ButtonSpriteRepository &button_sprite_repository,
                                         TextSpriteRepository &text_sprite_repository)
        : LoginState(login_, button_sprite_repository, text_sprite_repository) {
  std::map<uint16_t, std::vector<ClientData>> matches_info;
  login.getListOfMatchesInfo(matches_info);
  for (auto &match_info: matches_info) {
    auto button = make_unique<PickMatchButton>(button_sprite_repository,
                                               text_sprite_repository,
                                               match_info.second,
                                               match_info.first);
    button_list.push_back(std::move(button));
  }
}

bool ConnectToMatchState::clientIsConnectedToMatch() {
  return false;
}

void
ConnectToMatchState::render(LoginScene &login_renderer) {
  login_renderer.renderMatchButtons(button_list);
}

void ConnectToMatchState::fillWithActiveButtons(
        std::list<std::reference_wrapper<Button>> &active_buttons) {
  for (auto &button: button_list)
    active_buttons.emplace_back(*button);
}

void ConnectToMatchState::fillWithActiveTextEntryButtons(
        std::list<std::reference_wrapper<TextEntryButton>> &
        active_text_entries) {
  //dont have text_entries
}

int ConnectToMatchState::processTokens(std::list<std::string> &&tokens) {
  std::string str_match_number = tokens.front();
  int match_number = std::stoi(str_match_number);
  login.chooseMatchNumber(match_number);
  return NEXT_STATE_SELECTING_ROLE;
}

ConnectedToMatchState::ConnectedToMatchState(Login &login_,
                                             ButtonSpriteRepository &button_sprite_repository,
                                             TextSpriteRepository &text_sprite_repository)
        : LoginState(login_, button_sprite_repository,
                     text_sprite_repository) {}

bool ConnectedToMatchState::clientIsConnectedToMatch() {
  return true;
}

void
ConnectedToMatchState::render(LoginScene &login_scene) {
//  login_scene.renderConnectedSprite(loading_background);
}

void ConnectedToMatchState::fillWithActiveButtons(
        std::list<std::reference_wrapper<Button>> &active_buttons) {}

void ConnectedToMatchState::fillWithActiveTextEntryButtons(
        std::list<std::reference_wrapper<TextEntryButton>> &
        active_text_entries) {}

int ConnectedToMatchState::processTokens(std::list<std::string> &&tokens) {
  return NO_NEXT_STATE;
}
