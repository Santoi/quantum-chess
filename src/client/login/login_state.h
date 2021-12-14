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
#include <string>
#include <list>

#define NEXT_STATE_CONNECT_TO_MATCH 1
#define NEXT_STATE_SELECTING_ROLE 2
#define NEXT_STATE_CONNECTED_TO_MATCH 3
#define RETURN_TO_SELECTING_MATCH_STATE -2
#define STOP_PLAYING -5
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

  // render state accordingly
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

  //It pops from the list of tokens the ip, port and nickname
  //It calls login method connectToServer
  // It returns NEXT_STATE_CONNECT_TO_MATCH
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

  // Returns false
  bool clientIsConnectedToMatch() override;

  // Render at most matches_per_page match buttons, and control buttons
  void render(LoginScene &login_scene) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  // Increments page, decreces page, refreshes page, or sets chosen match id
  // The next state is return according to the clicked button:
  // KEEP_STATE if next or prev buttons are pressed
  // NEXT_STATE_CONNECT_TO_MATCH if matches are refreshed
  // NEXT_STATE_SELECTING_ROLE if a match is picked
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

  // If tokens is empty then exception UnavailableRoleException is thrown,
  // else the selected role is assigned and NEXT_STATE_CONNECTED_TO_MATCH is
  // returned
  int processTokens(std::list<std::string> &&tokens) override;

  ~SelectingRoleState() override = default;

private:
  // Creates and adds RoleButton to list of buttons according to if role_ is in
  // the available_roles list.
  // Type string denotes the key to access the button image
  // in the button repository.
  void addActiveOrInactiveRoleButtonWithImages(
      ClientData::Role role_,
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

class ChooseToKeepPlayingState : public LoginState {
private:
    TextureSprite *question_sprite;

public:
    ChooseToKeepPlayingState(Login& login, ButtonSpriteRepository
                             &button_sprite_repository,
                             TextSpriteRepository &text_sprite_repository);

    bool clientIsConnectedToMatch() override;

    void render(LoginScene &login_scene) override;

    void fillWithActiveButtons(
            std::list<std::reference_wrapper<Button>> &active_buttons) override;

    void fillWithActiveTextEntryButtons(
            std::list<std::reference_wrapper<TextEntryButton>> &
            active_text_entries) override;

    int processTokens(std::list<std::string> &&tokens) override;

    ~ChooseToKeepPlayingState() override = default;
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_H
