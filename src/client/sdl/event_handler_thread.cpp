#include "event_handler_thread.h"
#include "../../common/chess_exception.h"
#include "../game/chat.h"
#include <iostream>
#include <list>

EventHandlerThread::EventHandlerThread(Window &window, Game &game,
                                       GameScene &game_scene,
                                       Chat &chat_, TextEntry &text_entry)
        : HandlerThread(true), window(window), game(game),
          game_scene(game_scene),
          text_entry(text_entry),
          split(false), merge(false),
          first_click(false), second_click(false), penultimate_click(),
          last_click(), chat(chat_) {}

void EventHandlerThread::run() {
  while (true) {
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
        if (mouse.button == SDL_BUTTON_LEFT)
          handleMouseButtonLeft(mouse);
        else if (mouse.button == SDL_BUTTON_RIGHT)
          handleMouseButtonRight(mouse);
        break;
    }
  }
}

bool EventHandlerThread::isOpen() {
  return open;
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
    case SDLK_r: {
      if (!text_entry.isEnabled()) {
        std::cout << "r!" << std::endl;
        if (game_scene.renderingHelpScreen())
          return;
        game_scene.startRenderingLeaveScreen();
      }
      break;
    }
    case SDLK_c: {
      if (!text_entry.isEnabled()) {
        std::cout << "c!" << std::endl;
        if (!game_scene.renderingLeaveMatchScreen())
          return;
        game_scene.stopRenderingLeaveScreen();
      }
      break;
    }
    case SDLK_y: {
      if (!text_entry.isEnabled()) {
        std::cout << "y!" << std::endl;
        if (!game_scene.renderingLeaveMatchScreen())
          return;
        open = false;
      }
      break;
    }
    case SDLK_s: {
      if (!text_entry.isEnabled()) {
        std::cout << "s!" << std::endl;
        if (!game_scene.renderingLeaveMatchScreen())
          return;
        game.surrender();
      }
      break;
    }
    case SDLK_o: {
      if (!text_entry.isEnabled()) {
        std::cout << "o!" << std::endl;
        if (!game_scene.renderingLeaveMatchScreen())
          return;
        //game.request tie()
      }
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

void EventHandlerThread::handleMouseButtonLeft(SDL_MouseButtonEvent &mouse) {
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

    std::list<Position> coords;
    for (size_t i = 0; i < 8; i++) {
      Position pos(0, i);
      coords.push_back(pos);
    }
    if (!first_click) { // actually, if this is the first click
      game.currentTile(pixel);
      if (split)
        game.askSplitTiles(pixel);
      else if (merge)
        game.askMergeTiles(pixel);
      else
        game.askMoveTiles(pixel);
      first_click = true;
      last_click = pixel;
      return;
    }

    if (!second_click) { // actually, if this is the second click
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
      return;
    }

    // third click
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
  catch(const ChessException &e) {
    std::cerr << e.what() << std::endl;
  }
}

void EventHandlerThread::handleMouseButtonRight(SDL_MouseButtonEvent &mouse) {
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

void EventHandlerThread::handleWindowChange(SDL_WindowEvent &window_event) {
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
