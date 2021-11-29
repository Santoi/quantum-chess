#include "event_handler_thread.h"
#include "../game/chess_exception.h"
#include <iostream>
#include <list>

EventHandlerThread::EventHandlerThread(Window &window, Game &game)
    : window(window), open(true), game(game),
      split(false), merge(false),
      first_click(false) {}

void EventHandlerThread::run() {
  while (true) {
    SDL_WaitEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
        open = false;
        return;
      case SDL_WINDOWEVENT:
        handleWindowChange(event.window);
      case SDL_KEYDOWN:
        handleKeyDown();
        break;
      case SDL_KEYUP:
        handleKeyUp();
        break;
      case SDL_MOUSEBUTTONDOWN:
        SDL_MouseButtonEvent mouse = event.button;
        if (mouse.button == SDL_BUTTON_LEFT)
          handleMouseButtonLeft(mouse);
        else if (mouse.button == SDL_BUTTON_RIGHT)
          handleMouseButtonRight(mouse);
    }
  }
}

bool EventHandlerThread::isOpen() {
  return open;
}

void EventHandlerThread::handleKeyDown() {
  switch (event.key.keysym.sym) {
    case SDLK_ESCAPE: {
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
    if (!game.isPixelInBoard(pixel))
      return;

    std::list<Position> coords;
    for (size_t i = 0; i < 8; i++) {
      Position pos(0, i);
      coords.push_back(pos);
    }
    if (!first_click) {
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

    if (!second_click) {
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
  catch (const ChessException &e) {
    std::cerr << e.what() << std::endl;
  }
}

void EventHandlerThread::handleMouseButtonRight(SDL_MouseButtonEvent &mouse) {
  PixelCoordinate pixel(mouse.x, mouse.y);
  // board is set default here because is needed to color the two at the same
  // time.
  game.setDefaultBoard();
  game.askEntangledTiles(pixel);
  game.askQuantumTiles(pixel);
}

void EventHandlerThread::handleWindowChange(SDL_WindowEvent &window_event) {
  if (window_event.event == SDL_WINDOWEVENT_RESIZED) {
    window.setMaxHeight(window_event.data1 / window.getMinRatio());
  }
  // TODO: fix fullscreen
}
