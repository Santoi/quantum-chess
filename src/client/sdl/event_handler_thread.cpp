#include "event_handler_thread.h"
#include "../../common/chess_exception.h"
#include "screen_handler.h"
#include "../game/chat.h"
#include <iostream>
#include <list>
#include <string>

EventHandlerThread::EventHandlerThread(Window &window, Game &game,
                                       ScreenHandler &screen_handler_,
                                       Chat &chat_, TextEntry &text_entry)
        : HandlerThread(true), window(window), game(game),
          screen_handler(screen_handler_),
          text_entry(text_entry),
          split(false), merge(false),
          first_click(false), second_click(false), penultimate_click(),
          last_click(), chat(chat_) {}

void EventHandlerThread::run() {
  while (open) {
    SDL_WaitEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
        open = false;
        return;
      case SDL_WINDOWEVENT:
        handleWindowChange(event.window);
        break;
      case SDL_TEXTINPUT:
        handleTextInput(event.text.text);
        break;
      case SDL_KEYDOWN:
        handleKeyDown();
        break;
      case SDL_KEYUP:
        handleKeyUp();
        break;
      case SDL_MOUSEBUTTONDOWN: // Any extra case must be added above this one
        SDL_MouseButtonEvent mouse = event.button;
        if (!screen_handler.renderingGame())
          break;
        if (mouse.button == SDL_BUTTON_LEFT)
          handleMouseButtonLeft(mouse);
        else if (mouse.button == SDL_BUTTON_RIGHT)
          handleMouseButtonRight(mouse);
        break;
    }
  }
}

void EventHandlerThread::handleKeyDown() {
  switch (event.key.keysym.sym) {
    case SDLK_ESCAPE: {
      text_entry.disableEntry();
      chat.disable();
      game.setDefaultBoard();
      first_click = false;
      second_click = false;
      split = false;
      merge = false;
      break;
    }
    case SDLK_LSHIFT: {
      split = true;
      merge = false;
      break;
    }
    case SDLK_LCTRL: {
      merge = true;
      split = false;
      break;
    }
    case SDLK_f: {
      if (!text_entry.isEnabled()) {
        first_click = second_click = false;
        game.flipBoard();
      }
      break;
    }
    case SDLK_n: {
      if (!text_entry.isEnabled())
        game.toggleSounds();
      break;
    }
    case SDLK_m: {
      if (!text_entry.isEnabled())
        game.toggleMusic();
      break;
    }
    case SDLK_h: {
      if (!text_entry.isEnabled()) {
        screen_handler.toggleHelpScreen();
      }
      break;
    }
    case SDLK_r: {
      if (!text_entry.isEnabled()) {
        screen_handler.activateLeaveScreen();
      }
      break;
    }
    case SDLK_c: {
      if (!text_entry.isEnabled()) {
        screen_handler.deactivateLeaveScreen();
      }
      break;
    }
    case SDLK_y: {
      if (!text_entry.isEnabled())
        screen_handler.switchOpenStatusIfLeaveMatchScreenIsRendering(open);
      break;
    }
    case SDLK_s: {
      if (!text_entry.isEnabled())
        screen_handler.surrenderMatchIfLeaveMatchScreenIsRendering(game);
      break;
    }
    case SDLK_BACKSPACE: {
      if (text_entry.isEnabled())
        text_entry.backspace();
      break;
    }
    case SDLK_RETURN: {
      if (text_entry.isEnabled()) {
        chat.sendMessage(text_entry.getText());
        text_entry.clear();
      }
      break;
    }
  }
}

void EventHandlerThread::handleKeyUp() {
  switch (event.key.keysym.sym) {
    case SDLK_LSHIFT: {
      if (!first_click)
        split = false;
      break;
    }
    case SDLK_LCTRL: {
      if (!first_click)
        merge = false;
      break;
    }
  }
}

void EventHandlerThread::handleMouseButtonLeft(const SDL_MouseButtonEvent
                                               &mouse) {
  try {
    PixelCoordinate pixel(mouse.x, mouse.y);
    if (chat.enableIfPixelIsInChat(pixel)) {
      text_entry.enableEntry();
      return;
    }
    text_entry.disableEntry();

    if (!game.isPixelInBoard(pixel)) {
      return;
    }

    std::list<BoardPosition> coords;
    for (size_t i = 0; i < 8; i++) {
      BoardPosition pos(0, i);
      coords.push_back(pos);
    }

    if (!first_click) { // actually, if this is the first click
      handleUserFirstClick(pixel);
      return;
    }

    if (!second_click) { // actually, if this is the second click
      handleUserSecondClick(pixel);
      return;
    }

    // third click
    handleUserThirdClick(pixel);
  }
  catch(const ChessException &e) {
    std::cerr << e.what() << std::endl;
  }
}

void EventHandlerThread::handleMouseButtonRight(const SDL_MouseButtonEvent
                                                      &mouse) {
  PixelCoordinate pixel(mouse.x, mouse.y);
  if (!game.isPixelInBoard(pixel)) {
    text_entry.disableEntry();
    return;
  }
  // board is set default here because is needed to color the two at the same
  // time.
  game.setDefaultBoard();
  game.askEntangledTiles(pixel);
  game.askQuantumTiles(pixel);
}

void
EventHandlerThread::handleWindowChange(const SDL_WindowEvent &window_event) {
  if (window_event.event == SDL_WINDOWEVENT_RESIZED) {
    // TODO solo anda en el de santi
    window.setMaxHeight(window_event.data1 / window.getMinRatio());
    // TODO santi ver esto del resize
    /*if (window_event.data1 < window_event.data2 / window.getMinRatio())
      window.setSize(window_event.data2 * window.getMinRatio(),
                     window_event.data2);*/
  }
  // TODO: fix fullscreen // solo se rompe en el de santi
}

void EventHandlerThread::handleTextInput(const std::string &text) {
  if (text_entry.isEnabled())
    if (!text_entry.concat(text)) {
      chat.sendMessage(text_entry.getText());
      text_entry.clear();
    }
}

void EventHandlerThread::handleUserFirstClick(const PixelCoordinate &pixel) {
  game.currentTile(pixel);
  if (split)
    game.askSplitTiles(pixel);
  else if (merge)
    game.askMergeTiles(pixel);
  else
    game.askMoveTiles(pixel);
  first_click = true;
  last_click = pixel;
}

void EventHandlerThread::handleUserSecondClick(const PixelCoordinate &pixel) {
  if (split) {
    penultimate_click = last_click;
    last_click = pixel;
    second_click = true;
  } else if (merge) {
    penultimate_click = last_click;
    game.askMergeTiles(pixel, last_click);
    last_click = pixel;
    second_click = true;
  } else {
    game.moveChessman(last_click, pixel);
    game.setDefaultBoard();
    first_click = false;
  }
}

void EventHandlerThread::handleUserThirdClick(const PixelCoordinate &pixel) {
  if (split) {
    game.splitChessman(penultimate_click, last_click, pixel);
    game.setDefaultBoard();
    first_click = false;
    second_click = false;
    split = false;
  }
  if (merge) {
    game.mergeChessman(penultimate_click, last_click, pixel);
    game.setDefaultBoard();
    first_click = false;
    second_click = false;
    merge = false;
  }
}
