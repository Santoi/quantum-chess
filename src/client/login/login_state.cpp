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
  for (auto &button: buttons_ptr)
    button->resetButton();
}

ConnectingToServerState::ConnectingToServerState(Login &login_,
                                                 ButtonSpriteRepository &button_sprite_repository,
                                                 TextSpriteRepository &text_sprite_repository)
        : LoginState(login_, button_sprite_repository, text_sprite_repository) {
  text_entry_buttons_ptr.push_back(std::move(make_unique<TextEntryButton>(button_sprite_repository,
                                                                          text_sprite_repository, "IP")));
  text_entry_buttons_ptr.push_back(std::move(make_unique<TextEntryButton>(button_sprite_repository,
                                                                          text_sprite_repository, "PORT")));
  text_entry_buttons_ptr.push_back(std::move(make_unique<TextEntryButton>(button_sprite_repository,
                                                                            text_sprite_repository, "NICK NAME")));
  buttons_ptr.push_back(std::move(make_unique<ConnectButton>(button_sprite_repository,
                                                             text_sprite_repository,
                                                             "CONNECT",
                                                             text_entry_buttons_ptr)));
}

bool ConnectingToServerState::clientIsConnectedToMatch() {
  return false;
}

void ConnectingToServerState::render(LoginScene &login_scene) {
  login_scene.renderIPAndPortFields(*buttons_ptr[0],
                                    *text_entry_buttons_ptr[0], *text_entry_buttons_ptr[1],
                                    *text_entry_buttons_ptr[2]);
}

void ConnectingToServerState::fillWithActiveButtons(
        std::list<std::reference_wrapper<Button>> &active_buttons) {
  for (auto &button: buttons_ptr)
    active_buttons.emplace_back(*button);
}

void ConnectingToServerState::fillWithActiveTextEntryButtons(
        std::list<std::reference_wrapper<TextEntryButton>> &
        active_text_entries) {
  for (auto &button: text_entry_buttons_ptr)
    active_text_entries.emplace_back(*button);
}

int ConnectingToServerState::processTokens(std::list<std::string> &&tokens) {
  std::string ip = tokens.front(); //tokens strings has the same order as how TextEntryButton are in the list
  //(first the ip string, second the port string)
  tokens.pop_front();
  std::cout << ip << std::endl;
  std::string port = tokens.front();
  tokens.pop_front();
  std::cout << port << std::endl;
  login.connectToServer(ip, port);
  std::string nick_name = tokens.front();
  std::cout << nick_name << std::endl;
  login.saveNickName(nick_name);
  return NEXT_STATE_CONNECT_TO_MATCH;
}

SelectingMatchState::SelectingMatchState(Login &login_,
                                         ButtonSpriteRepository &button_sprite_repository,
                                         TextSpriteRepository &text_sprite_repository)
        : LoginState(login_, button_sprite_repository, text_sprite_repository) {
   login.fillVectorWithMatchButtons(buttons_ptr, button_sprite_repository, text_sprite_repository);
}

bool SelectingMatchState::clientIsConnectedToMatch() {
    return false;
}

void
SelectingMatchState::render(LoginScene &login_renderer) {
    login_renderer.renderMatchButtons(buttons_ptr);
}

void SelectingMatchState::fillWithActiveButtons(
        std::list<std::reference_wrapper<Button>> &active_buttons) {
    for (auto &button: buttons_ptr)
        active_buttons.emplace_back(*button);
}

void SelectingMatchState::fillWithActiveTextEntryButtons(
        std::list<std::reference_wrapper<TextEntryButton>> &
        active_text_entries) {
    //dont have text_entries_ptr
}

int SelectingMatchState::processTokens(std::list<std::string> &&tokens) {
    std::string str_match_number = tokens.front();
    int match_number = std::stoi(str_match_number);
    login.chooseMatchNumber(match_number);
    return NEXT_STATE_SELECTING_ROLE;
}

void SelectingRoleState::addActiveOrInactiveRoleButtonWithImages(ClientData::Role role_,
                                                                 ButtonSpriteRepository &button_repository,
                                                                 TextSpriteRepository &text_repository,
                                                                 std::list<ClientData::Role>& available_roles,
                                                                 const std::string& available_not_pressed_image,
                                                                 const std::string& available_pressed_image,
                                                                 const std::string& not_available_not_pressed_image,
                                                                 const std::string& not_available_pressed_image) {
    std::unique_ptr<RoleButton> role_button_ptr;
    std::list<ClientData::Role>::iterator findIter = std::find(available_roles.begin(),
                                                               available_roles.end(), role_);
    if (findIter != available_roles.end())
        role_button_ptr = make_unique<RoleButton>(button_repository, text_repository, role_, true);
    else
        role_button_ptr = make_unique<RoleButton>(button_repository, text_repository, role_, false);
    buttons_ptr.push_back(std::move(role_button_ptr));
}

SelectingRoleState::SelectingRoleState(Login &login_, ButtonSpriteRepository &button_repository,
                                       TextSpriteRepository &text_repository)
        :LoginState(login_, button_repository, text_repository) {
    std::list<ClientData::Role> available_roles = login.getAvailableRoles();
    addActiveOrInactiveRoleButtonWithImages(ClientData::ROLE_WHITE, button_repository, text_repository,
                                            available_roles,
                                            "img/buttons/available_white_role.png",
                                            "img/buttons/available_white_role.png",
                                            "img/buttons/not_available_white_role.png",
                                            "img/buttons/not_available_white_role.png");
    addActiveOrInactiveRoleButtonWithImages(ClientData::ROLE_BLACK, button_repository, text_repository,
                                            available_roles,
                                            "img/buttons/available_black_role.png",
                                            "img/buttons/available_black_role.png",
                                            "img/buttons/not_available_black_role.png",
                                            "img/buttons/not_available_black_role.png");
    addActiveOrInactiveRoleButtonWithImages(ClientData::ROLE_SPECTATOR, button_repository, text_repository,
                                            available_roles,
                                            "img/buttons/spectator_role.png",
                                            "img/buttons/spectator_role.png",
                                            "img/buttons/spectator_role.png",
                                            "img/buttons/spectator_role.png");
}



bool SelectingRoleState::clientIsConnectedToMatch() {
  return false;
}

void
SelectingRoleState::render(LoginScene &login_scene) {
  login_scene.renderRolesButtons(*buttons_ptr[0],
                                 *buttons_ptr[1],
                                 *buttons_ptr[2]);
}

void SelectingRoleState::fillWithActiveButtons(
        std::list<std::reference_wrapper<Button>> &active_buttons) {
  for (auto &button: buttons_ptr)
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
