#include "login_handler_thread.h"
#include "../sdl/button.h"
#include "../sdl/text_entry_button.h"
#include <list>

LoginHandlerThread::LoginHandlerThread(Login &login,
                                       LoginStateHandler &login_state_handler) :
    HandlerThread(true),
    login(login),
    login_state_handler(login_state_handler),
    expecting_text_entry(false),
    was_closed_(false) {}

void LoginHandlerThread::run() {
  while (!(login_state_handler.clientIsConnectedToMatch())) {
    SDL_WaitEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
        was_closed_ = true;
        open = false;
        return;
      case SDL_KEYDOWN:
        handleKeyDown();
        break;
      case SDL_TEXTINPUT:
        if (expecting_text_entry)
          handleTextInput(event.text.text);
        break;
      case SDL_MOUSEBUTTONDOWN:
        SDL_MouseButtonEvent mouse = event.button;
        if (mouse.button == SDL_BUTTON_LEFT)
          handleMouseButtonLeft(mouse);
    }
  }
  open = false;
}

void LoginHandlerThread::handleKeyDown() {
  std::list<std::reference_wrapper<TextEntryButton>> active_text_entries;
  login_state_handler.fillWithActiveTextEntryButtons(active_text_entries);
  switch (event.key.keysym.sym) {
    case SDLK_ESCAPE: {
      expecting_text_entry = false;
      for (auto &active_text_entry: active_text_entries)
        active_text_entry.get().disableTextEntry();
      break;
    }
    case SDLK_BACKSPACE: {
      for (auto &active_text_entry: active_text_entries)
        active_text_entry.get().backspaceIfEnabled();
      break;
    }
  }
}

void LoginHandlerThread::handleTextInput(const std::string &new_text) {
  std::list<std::reference_wrapper<TextEntryButton>> active_text_entries;
  login_state_handler.fillWithActiveTextEntryButtons(active_text_entries);
  for (auto &active_text_entry: active_text_entries)
    active_text_entry.get().concatIfEnabled(new_text);
}

void LoginHandlerThread::handleMouseButtonLeft(SDL_MouseButtonEvent &mouse) {
  PixelCoordinate pixel(mouse.x, mouse.y);
  std::list<std::reference_wrapper<Button>> active_buttons;
  login_state_handler.fillWithActiveButtons(active_buttons);
  auto it = active_buttons.begin();
  std::list<std::string> tokens;
  while (it != active_buttons.end()) {
    if (it->get().fillTokensIfClicked(pixel, tokens))
      break;
    ++it;
  }
  if (it != active_buttons.end()) {
    login_state_handler.processTokens(std::move(tokens));
  } else { //first disable all text entries
    std::list<std::reference_wrapper<TextEntryButton>> active_text_entries;
    login_state_handler.fillWithActiveTextEntryButtons(active_text_entries);
    for (auto &active_text_entry: active_text_entries)
      active_text_entry.get().disableTextEntry();
    //enable text entry if pressed
    expecting_text_entry = false;
    auto it2 = active_text_entries.begin();
    while (it2 != active_text_entries.end()) {
      if (it2->get().enableTextEntryIfClicked(pixel))
        expecting_text_entry = true;
      ++it2;
    }
//    expecting_text_entry = it2 != active_text_entries.end();
  }
}

bool LoginHandlerThread::was_closed() const {
  return was_closed_;
}
