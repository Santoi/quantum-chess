#include "login_state.h"
#include "../../common/unique_ptr.h"
#include "../../common/client_data.h"
#include "unavailable_role_exception.h"
#include "invalid_nick_name_exception.h"
#include <iostream>

#define MATCHES_PER_PAGE 8

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
  text_entry_buttons_ptr.push_back(
      make_unique<TextEntryButton>(button_sprite_repository,
                                   text_sprite_repository,
                                   "IP"));
  text_entry_buttons_ptr.push_back(
      make_unique<TextEntryButton>(button_sprite_repository,
                                   text_sprite_repository,
                                   "PORT"));
  text_entry_buttons_ptr.push_back(
      make_unique<TextEntryButton>(button_sprite_repository,
                                   text_sprite_repository,
                                   "NICK NAME"));
  buttons_ptr.push_back(
      make_unique<ConnectButton>(button_sprite_repository,
                                 text_sprite_repository,
                                 "CONNECT",
                                 text_entry_buttons_ptr));
}

bool ConnectingToServerState::clientIsConnectedToMatch() {
  return false;
}

void ConnectingToServerState::render(LoginScene &login_scene) {
  login_scene.renderConnectionToServerButtons(*buttons_ptr[0],
                                              *text_entry_buttons_ptr[0],
                                              *text_entry_buttons_ptr[1],
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
  std::string port = tokens.front();
  tokens.pop_front();
  std::string nick_name = tokens.front();
  size_t length = nick_name.size();
  if (length < MIN_NICK_NAME_LENGTH || length > MAX_NICK_NAME_LENGTH)
    throw InvalidNickNameException();
  login.connectToServer(ip, port);
  login.saveNickName(nick_name);
  return NEXT_STATE_CONNECT_TO_MATCH;
}

SelectingMatchState::SelectingMatchState(Login &login_,
                                         ButtonSpriteRepository &button_sprite_repository,
                                         TextSpriteRepository &text_sprite_repository)
    : LoginState(login_, button_sprite_repository, text_sprite_repository),
      next_matches_button(button_sprite_repository, text_sprite_repository),
      previous_matches_button(button_sprite_repository,
                              text_sprite_repository),
      refresh_matches_button(button_sprite_repository, text_sprite_repository),
      matches_page(0),
      matches_per_page(MATCHES_PER_PAGE) {
  std::vector<ClientData> empty_clients_list;
  buttons_ptr.push_back(
      make_unique<PickMatchButton>(button_sprite_repository,
                                   text_sprite_repository,
                                   empty_clients_list,
                                   0));
  std::map<uint16_t, std::vector<ClientData>> match_info;
  login.getListOfMatchesInfo(match_info);
  for (auto it = match_info.begin(); it != match_info.end(); ++it)
    buttons_ptr.push_back(
        make_unique<PickMatchButton>(button_sprite_repository,
                                     text_sprite_repository,
                                     it->second,
                                     it->first));
}

bool SelectingMatchState::clientIsConnectedToMatch() {
  return false;
}

void
SelectingMatchState::render(LoginScene &login_scene) {
  login_scene.renderChoosingMatchButtons(buttons_ptr, next_matches_button,
                                         previous_matches_button,
                                         refresh_matches_button, matches_page,
                                         matches_per_page);
}

void SelectingMatchState::fillWithActiveButtons(
    std::list<std::reference_wrapper<Button>> &active_buttons) {
  for (auto &button: buttons_ptr)
    active_buttons.emplace_back(*button);
  active_buttons.emplace_back(next_matches_button);
  active_buttons.emplace_back(previous_matches_button);
  active_buttons.emplace_back(refresh_matches_button);
}

void SelectingMatchState::fillWithActiveTextEntryButtons(
    std::list<std::reference_wrapper<TextEntryButton>> &
    active_text_entries) {
  //dont have text_entries_ptr
}

int SelectingMatchState::processTokens(std::list<std::string> &&tokens) {
  int next_state = NEXT_STATE_SELECTING_ROLE;
  std::string clicked_button = tokens.front();
  if (clicked_button == "NEXT") {
    if (buttons_ptr.size() > (matches_page + 1) * matches_per_page)
      matches_page++;
    next_state = KEEP_STATE;
  } else if (clicked_button == "PREV") {
    if (matches_page > 0)
      matches_page--;
    next_state = KEEP_STATE;
  } else {
    int match_number = std::stoi(clicked_button);
    if (match_number == UINT16_MAX) {
      login.refreshMatches();
      next_state = NEXT_STATE_CONNECT_TO_MATCH;
    } else {
      login.chooseMatchNumber(match_number);
      login.sendSavedNickNameToServer();
    }
  }
  return next_state;
}

void SelectingRoleState::addActiveOrInactiveRoleButtonWithImages(
    ClientData::Role role_,
    ButtonSpriteRepository &button_repository,
    TextSpriteRepository &text_repository,
    std::list<ClientData::Role> &available_roles,
    std::string &&type) {
  std::unique_ptr<RoleButton> role_button_ptr;
  std::list<ClientData::Role>::iterator findIter = std::find(
      available_roles.begin(),
      available_roles.end(), role_);
  if (findIter != available_roles.end())
    role_button_ptr = make_unique<RoleButton>(button_repository,
                                              text_repository, role_,
                                              std::move(type), true);
  else
    role_button_ptr = make_unique<RoleButton>(button_repository,
                                              text_repository, role_,
                                              std::move(type), false);
  buttons_ptr.push_back(std::move(role_button_ptr));
}

SelectingRoleState::SelectingRoleState(Login &login_,
                                       ButtonSpriteRepository &button_repository,
                                       TextSpriteRepository &text_repository)
    : LoginState(login_, button_repository, text_repository) {
  std::list<ClientData::Role> available_roles = login.getAvailableRoles();
  addActiveOrInactiveRoleButtonWithImages(ClientData::ROLE_WHITE,
                                          button_repository, text_repository,
                                          available_roles, "role_white");
  addActiveOrInactiveRoleButtonWithImages(ClientData::ROLE_BLACK,
                                          button_repository, text_repository,
                                          available_roles, "role_black");
  addActiveOrInactiveRoleButtonWithImages(ClientData::ROLE_SPECTATOR,
                                          button_repository, text_repository,
                                          available_roles, "role_spectator");
  buttons_ptr.emplace_back(std::move(
          make_unique<ReturnToMatchSelectionButton>(button_repository,
                                                     text_repository,"action")));
}

bool SelectingRoleState::clientIsConnectedToMatch() {
  return false;
}

void
SelectingRoleState::render(LoginScene &login_scene) {
  login_scene.renderRolesButtons(*buttons_ptr[0],
                                 *buttons_ptr[1],
                                 *buttons_ptr[2],
                                 *buttons_ptr[3]);
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
  if (tokens.front() == "return")
    return RETURN_TO_SELECTING_MATCH_STATE;
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

void ConnectedToMatchState::render(LoginScene &login_scene) {
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

ChooseToKeepPlayingState::ChooseToKeepPlayingState(Login& login_,
                                                   ButtonSpriteRepository &button_sprite_repository,
                                                   TextSpriteRepository &text_sprite_repository)
                         :LoginState(login_, button_sprite_repository, text_sprite_repository) {
  buttons_ptr.push_back(std::move(
          make_unique<OptionButton>(button_sprite_repository,
                                      text_sprite_repository, "YES", "yes")));
  buttons_ptr.push_back(std::move(
          make_unique<OptionButton>(button_sprite_repository,
                                    text_sprite_repository, "NO", "no")));
}

bool ChooseToKeepPlayingState::clientIsConnectedToMatch() {
  return false;
}

void ChooseToKeepPlayingState::render(LoginScene &login_scene) {
  login_scene.renderLeaveMatchOptionButtons(*buttons_ptr[0],
                                            *buttons_ptr[1]);
}

void ChooseToKeepPlayingState::fillWithActiveButtons(
        std::list<std::reference_wrapper<Button>> &active_buttons) {
  for (auto &button: buttons_ptr)
    active_buttons.emplace_back(*button);
}

void ChooseToKeepPlayingState::fillWithActiveTextEntryButtons(
        std::list<std::reference_wrapper<TextEntryButton>> &
        active_text_entries) {
  //dont have any text entries
}

int ChooseToKeepPlayingState::processTokens(std::list<std::string> &&tokens) {
  if (tokens.front() == "yes")
    return RETURN_TO_SELECTING_MATCH_STATE;
  else
    return STOP_PLAYING;
}

