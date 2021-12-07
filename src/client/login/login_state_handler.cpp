#include "login_state_handler.h"
#include "../../common/src/unique_ptr.h"
#include "../../common/src/network_address_info_exception.h"
#include "unavailable_role_exception.h"

LoginStateHandler::LoginStateHandler(Login &login,
                                     ButtonSpriteRepository &button_repository,
                                     TextSpriteRepository &text_repository)
    : login(),
      button_repository(button_repository),
      text_repository(text_repository),
      current_state(make_unique<ConnectToServerState>(login, button_repository,
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
    sleep(1); // TODO mati ver
    std::lock_guard<std::mutex> lock_guard(mutex);
    current_state.reset();
    if (aux == 1)
      current_state = make_unique<ConnectToMatchState>(login,
                                                       button_repository,
                                                       text_repository);
    else if (aux == 2)
      current_state = make_unique<SelectingRoleState>(login,
                                                      button_repository,
                                                      text_repository);
    else if (aux == 3)
      current_state = make_unique<ConnectedToMatchState>(login,
                                                         button_repository,
                                                         text_repository);
  } catch(const NetworkAddressInfoException &error) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "ERROR",
                             "IP y/o puerto no válido. Por favor, vuelvalo a intentar.",
                             nullptr);
    current_state->resetPressedButtons();
    std::cout << "Error: " << error.what() << std::endl;
    return;
  } catch(const UnavailableRoleException &error) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "ERROR",
                             "El rol seleccionado no está disponible. Seleccione otro.",
                             nullptr);
    current_state->resetPressedButtons();
    std::cout << "Error: " << error.what() << std::endl;
    return;
  } catch(const std::exception &e) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "ERROR",
                             "IP y/o puerto no válido. Por favor, vuelvalo a intentar.",
                             nullptr);
    current_state->resetPressedButtons();
    std::cout << "Error: " << e.what() << std::endl;
    return;
  } catch(...) {
  }
}

void LoginStateHandler::render(LoginScene &login_scene) {
  std::lock_guard<std::mutex> lock_guard(mutex);
  current_state->render(login_scene);
}

Socket LoginStateHandler::getClientSocket() {
  return login.getClientSocket();
}

std::string LoginStateHandler::getClientNickName() {
  return login.getClientNickName();
}
