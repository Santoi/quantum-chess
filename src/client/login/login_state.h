#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_H

#include "../sdl/login_scene.h"
#include "../sdl/texture_sprite.h"
#include "login.h"
#include "../sdl/button.h"
#include "../sdl/text_entry_button.h"
#include <atomic>
#include <list>
#include <memory>

class LoginScene;

class LoginState {
protected:
  Login &login;
  ButtonSpriteRepository &button_sprite_repository;
  TextSpriteRepository &text_sprite_repository;
  std::list<std::unique_ptr<Button>> button_list;
  std::list<TextEntryButton> text_entry_button_list;

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
};

class ConnectToServerState : public LoginState {
public:

  ConnectToServerState(Login &login_,
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

  ~ConnectToServerState() override = default;
};

class ConnectToMatchState : public LoginState {
public:

  ConnectToMatchState(Login &login_,
                      ButtonSpriteRepository &button_sprite_repository,
                      TextSpriteRepository &text_sprite_repository);

  bool clientIsConnectedToMatch() override;

  void render(LoginScene &login_renderer) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  int processTokens(std::list<std::string> &&tokens) override;

  ~ConnectToMatchState() override = default;
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


#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_H
