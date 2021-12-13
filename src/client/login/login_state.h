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

  virtual bool clientIsConnectedToMatch() = 0;

  virtual void render(LoginScene &login_scene) = 0;

  virtual void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) = 0;

  virtual void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) = 0;

  virtual int processTokens(std::list<std::string> &&tokens) = 0;

  virtual ~LoginState() = default;

  void resetPressedButtons();
};

class ConnectingToServerState : public LoginState {
public:

  ConnectingToServerState(Login &login_,
                          ButtonSpriteRepository &button_sprite_repository,
                          TextSpriteRepository &text_sprite_repository);

  bool clientIsConnectedToMatch() override;

  void render(LoginScene &login_scene) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

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

  bool clientIsConnectedToMatch() override;

  void render(LoginScene &login_scene) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  int processTokens(std::list<std::string> &&tokens) override;

  ~SelectingMatchState() override = default;
};

class SelectingRoleState : public LoginState {
public:

  SelectingRoleState(Login &login_, ButtonSpriteRepository &button_repository,
                     TextSpriteRepository &text_repository);

  bool clientIsConnectedToMatch() override;

  void render(LoginScene &login_scene) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  int processTokens(std::list<std::string> &&tokens) override;

  ~SelectingRoleState() = default;

private:

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

  bool clientIsConnectedToMatch() override;

  void render(LoginScene &login_scene) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  int processTokens(std::list<std::string> &&tokens) override;

  ~ConnectedToMatchState() override = default;
};

class ChooseToKeepPlayingState : public LoginState {
private:
    TextureSprite *question_sprite;

public:
    ChooseToKeepPlayingState(Login& login, ButtonSpriteRepository &button_sprite_repository,
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
