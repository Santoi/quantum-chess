#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_H

#include "../sdl/login_scene.h"
#include "../sdl/texture_sprite.h"
#include "login.h"
#include "../logic/button.h"
#include "../logic/text_entry_button.h"
#include <atomic>
#include <vector>
#include <memory>

#define NEXT_STATE_CONNECT_TO_MATCH 1
#define NEXT_STATE_SELECTING_ROLE 2
#define NEXT_STATE_CONNECTED_TO_MATCH 3
#define NO_NEXT_STATE 0
#define KEEP_STATE -1

class LoginScene;

class LoginState {
protected:
  Login &login;
  ButtonSpriteRepository &button_sprite_repository;
  TextSpriteRepository &text_sprite_repository;
  std::vector<std::unique_ptr<Button>> buttons_ptr;
  std::vector<std::unique_ptr<TextEntryButton>> text_entry_buttons_ptr;

public:

  LoginState() = delete;

  LoginState(Login &login_,
             ButtonSpriteRepository &button_sprite_repository,
             TextSpriteRepository &text_sprite_repository);

  //Returns a boolean according to the derived State.
  virtual bool clientIsConnectedToMatch() = 0;

  //Derived State renders, via login_scene, its potential buttons and text entries.
  virtual void render(LoginScene &login_scene) = 0;

  virtual void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) = 0;

  virtual void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) = 0;

  //Derived State processes list of tokens, potentially communicating with the
  //server via login attribute.
  //It returns a int according to the next state.
  virtual int processTokens(std::list<std::string> &&tokens) = 0;

  virtual ~LoginState() = default;

  void resetAllButtonsToNotPressedState();
};

class ConnectingToServerState : public LoginState {
public:

  ConnectingToServerState(Login &login_,
                          ButtonSpriteRepository &button_sprite_repository,
                          TextSpriteRepository &text_sprite_repository);

  //Returns false.
  bool clientIsConnectedToMatch() override;

  //Renders connect button and ip, port and nick name text fields.
  void render(LoginScene &login_scene) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  //It pops from the list of tokens in the following order: ip, port and nickname.
  //If nickname is not valid (see InvalidNickNameException) this exception is thrown.
  //It calls login method connectToServer (check its documentation for possible exception
  //throwing). It returns NEXT_STATE_CONNECT_TO_MATCH macro.
  int processTokens(std::list<std::string> &&tokens) override;

  ~ConnectingToServerState() override = default;
};

class SelectingMatchState : public LoginState {
  NextMatchesButton next_matches_button;
  PreviousMatchesButton previous_matches_button;
  RefreshMatchesButton refresh_matches_button;
  size_t matches_page;
  size_t matches_per_page;

public:

  SelectingMatchState(Login &login_,
                      ButtonSpriteRepository &button_sprite_repository,
                      TextSpriteRepository &text_sprite_repository);

  //Returns false.
  bool clientIsConnectedToMatch() override;

  //Renders upto matches_per_page PickMatchButtons, along with theNextMatchesButton,
  //PreviousMatchesButton and RefreshMatchesButton.
  void render(LoginScene &login_scene) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  //If tokens.front is equal to "NEXT" and there are buttons in the next page,
  //then matches_page is incremented.
  //If it is equal to "PREV" and current matches_page is not the first page, then
  //matches_page is decremented.
  //For all of this four cases the KEEP_STATE macro is returned.
  //Else, tokens.front is considered to be a number. If this number equals UINT16_MAX
  //login method refreshMatches() is called and macro NEXT_STATE_CONNECT_TO_MATCH
  //is returned.
  //Finally, if number (k) is different than UINT16_MAX then login methods
  //sendChosenMatchToServer(k) and sendSavedNickNameToServer are called and macro
  //NEXT_STATE_SELECTING_ROLE is returned.
  int processTokens(std::list<std::string> &&tokens) override;

  ~SelectingMatchState() override = default;
};

class SelectingRoleState : public LoginState {
public:

  SelectingRoleState(Login &login_, ButtonSpriteRepository &button_repository,
                     TextSpriteRepository &text_repository);

  //Returns false.
  bool clientIsConnectedToMatch() override;

  //Renders all 3 role buttons.
  void render(LoginScene &login_scene) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  //If tokens is empty then exception UnavailableRoleException is thrown.
  //Else tokens.front is considered to be the selected role: it is transformed
  //from string to enum and sent to server via login method saveAndSendChosenRoleToServer.
  //Macro NEXT_STATE_CONNECTED_TO_MATCH is returned.
  int processTokens(std::list<std::string> &&tokens) override;

  ~SelectingRoleState() override = default;

private:

  //Creates and adds RoleButton to list of buttons according to if role_ is in
  //the available_roles list. Type string denotes the key to access the button image
  //in the button repository.
  void addActiveOrInactiveRoleButtonWithImages(ClientData::Role role_,
                                               ButtonSpriteRepository &button_repository,
                                               TextSpriteRepository &text_repository,
                                               std::list<ClientData::Role> &available_roles,
                                               std::string &&type);

  ClientData::Role getRoleFromString(const std::string &str_selected_role);
};

class ConnectedToMatchState : public LoginState {
//  Background loading_background;

public:
  ConnectedToMatchState(Login &login_,
                        ButtonSpriteRepository &button_sprite_repository,
                        TextSpriteRepository &text_sprite_repository);

  //Returns true.
  bool clientIsConnectedToMatch() override;

  //Renders nothing.
  void render(LoginScene &login_scene) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  //Automatically returns NO_NEXT_STATE macro.
  int processTokens(std::list<std::string> &&tokens) override;

  ~ConnectedToMatchState() override = default;
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_H
