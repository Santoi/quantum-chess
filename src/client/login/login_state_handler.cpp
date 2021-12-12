#include "login_state_handler.h"
#include "../../common/unique_ptr.h"
#include "../../common/network_address_info_exception.h"
#include "unavailable_role_exception.h"
#include "invalid_nick_name_exception.h"

LoginStateHandler::LoginStateHandler(Login &login,
                                     ButtonSpriteRepository &button_repository,
                                     TextSpriteRepository &text_repository)
    : login(login),
      button_repository(button_repository),
      text_repository(text_repository),
      current_state(
          make_unique<ConnectingToServerState>(login, button_repository,
                                               text_repository)) {}

bool LoginStateHandler::clientIsConnectedToMatch() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  return current_state->clientIsConnectedToMatch();
}

void LoginStateHandler::fillWithActiveButtons(
    std::list<std::reference_wrapper<Button>> &active_buttons) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  current_state->fillWithActiveButtons(active_buttons);
}

void LoginStateHandler::fillWithActiveTextEntryButtons(
  std::list<std::reference_wrapper<TextEntryButton>> &
  active_text_entries) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  current_state->fillWithActiveTextEntryButtons(active_text_entries);
}

void LoginStateHandler::processTokens(std::list<std::string> &&tokens) {
  try {
    int aux = current_state->processTokens(std::move(tokens));
    usleep(500000);
    std::lock_guard<std::mutex> lock_guard(mutex);
    if (aux != KEEP_STATE)
      current_state.reset();
    switch (aux) {
      case NEXT_STATE_CONNECT_TO_MATCH:
      case RETURN_TO_SELECTING_MATCH_STATE:
        if (aux == RETURN_TO_SELECTING_MATCH_STATE)
            login.reconnectToServer();
        current_state = make_unique<SelectingMatchState>(login,
                                                         button_repository,
                                                         text_repository);
        break;
      case NEXT_STATE_SELECTING_ROLE:
        current_state = make_unique<SelectingRoleState>(login,
                                                        button_repository,
                                                        text_repository);
        break;
      case NEXT_STATE_CONNECTED_TO_MATCH:
        current_state = make_unique<ConnectedToMatchState>(login,
                                                           button_repository,
                                                           text_repository);
        break;
      default:
        break;
    }
  } catch(const NetworkAddressInfoException &error) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "ERROR",
                             "Invalid IP:port. Try again.",
                             nullptr);
    current_state->resetPressedButtons();
    std::cerr << "Error: " << error.what() << std::endl;
    return;
  } catch(const UnavailableRoleException &error) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "ERROR",
                             "The selected role is unavailable. Select a different role.",
                             nullptr);
    current_state->resetPressedButtons();
    std::cerr << "Error: " << error.what() << std::endl;
    return;
  } catch(const InvalidNickNameException &error) {
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                               "ERROR",
                               error.what(),
                               nullptr);
      current_state->resetPressedButtons();
      std::cerr << "Error: " << error.what() << std::endl;
      return;
  } catch(const std::exception &e) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "ERROR",
                             "Invalid IP:port. Try again.",
                             nullptr);
    current_state->resetPressedButtons();
    std::cerr << "Error: " << e.what() << std::endl;
    return;
  } catch(...) {
    std::cerr << "Error: " << "unknown" << std::endl;
    return;
  }
}

void LoginStateHandler::render(LoginScene &login_scene) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  current_state->render(login_scene);
}

void LoginStateHandler::resetPressedButtons() {
  std::lock_guard<std::mutex> lock_guard(mutex);
  current_state->resetPressedButtons();
}
