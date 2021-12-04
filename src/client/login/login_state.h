#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_H

#include "../sdl/login_scene.h"
#include "../sdl/texture_sprite.h"
#include "login.h"
#include "../sdl/button.h"
#include "../sdl/text_entry_button.h"
#include <atomic>
#include <vector>
#include <memory>

class LoginScene;

class LoginState {
protected:
  Login &login;
  std::vector<std::unique_ptr<Button>> buttons_ptr;
  std::vector<std::unique_ptr<TextEntryButton>> text_entry_buttons_ptr;

public:

  LoginState() = delete;

  explicit LoginState(Login &login_);

  virtual bool clientIsConnectedToMatch() = 0;

  virtual void tellRendererWhatToRender(LoginScene &login_renderer) = 0;

  virtual void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) = 0;

  virtual void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) = 0;

  virtual int processTokens(std::list<std::string> &&tokens) = 0;

  ~LoginState() = default;
};

class NotConnectedToServerState : public LoginState {
public:

  NotConnectedToServerState(Login &login_, Renderer &renderer_);

  bool clientIsConnectedToMatch() override;

  void tellRendererWhatToRender(LoginScene &login_renderer) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  int processTokens(std::list<std::string> &&tokens) override;

  ~NotConnectedToServerState() = default;
};

class NotConnectedToMatchState : public LoginState {
public:

  NotConnectedToMatchState(Login &login_, Renderer &renderer_);

  bool clientIsConnectedToMatch() override;

  void tellRendererWhatToRender(LoginScene &login_renderer) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  int processTokens(std::list<std::string> &&tokens) override;

  ~NotConnectedToMatchState() = default;
};

class ConnectedToMatchState : public LoginState {
private:
  TextureSprite texture_sprite;

public:
  ConnectedToMatchState(Login &login_, Renderer &renderer_);

  bool clientIsConnectedToMatch() override;

  void tellRendererWhatToRender(LoginScene &login_renderer) override;

  void fillWithActiveButtons(
      std::list<std::reference_wrapper<Button>> &active_buttons) override;

  void fillWithActiveTextEntryButtons(
      std::list<std::reference_wrapper<TextEntryButton>> &
      active_text_entries) override;

  int processTokens(std::list<std::string> &&tokens) override;

  ~ConnectedToMatchState() = default;
};


#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_H
