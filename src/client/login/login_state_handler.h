#ifndef QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H
#define QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H

#include "login.h"
#include "login_state.h"
#include "../sdl/renderer.h"
#include <memory>
#include <mutex>

class LoginScene;

class LoginState;

class Button;

class TextEntryButton;

class LoginStateHandler {
protected:
  Login &login;
  ButtonSpriteRepository &button_repository;
  TextSpriteRepository &text_repository;
  std::unique_ptr<LoginState> current_state;
  bool continue_playing;
  std::mutex mutex;

public:
  LoginStateHandler() = delete;

  explicit LoginStateHandler(Login &login,
                             ButtonSpriteRepository &button_repository,
                             TextSpriteRepository &text_repository,
                             bool login_has_connected_to_server);

  bool clientIsConnectedToMatch();

  void fillWithActiveButtons(
          std::list<std::reference_wrapper<Button>> &active_buttons);

  void fillWithActiveTextEntryButtons(
          std::list<std::reference_wrapper<TextEntryButton>> &active_text_entries);

  void processTokens(std::list<std::string> &&tokens);

  void render(LoginScene &login_scene);
  
  ~LoginStateHandler() = default;

  void resetPressedButtons();

  bool loginIsNeeded();

    bool continuePlaying();
};

#endif //QUANTUM_CHESS_PROJ_LOGIN_STATE_HANDLER_H
