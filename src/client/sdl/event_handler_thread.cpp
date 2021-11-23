#include "event_handler_thread.h"
#include "../game/chess_exception.h"
#include <iostream>
#include <list>

EventHandlerThread::EventHandlerThread(Game &game) : open(true), game(game),
                                                     split(false), merge(false),
                                                     move(false) {}

void EventHandlerThread::run() {
  // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
  while (true) {
    SDL_WaitEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
        open = false;
        return;
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
      game.setDefaultBoard();
      move = false;
      break;
    }
    case SDLK_LSHIFT: {
      split = true;
      break;
    }
    case SDLK_LCTRL: {
      merge = true;
      break;
    }
  }
}

void EventHandlerThread::handleKeyUp() {
  switch (event.key.keysym.sym) {
    case SDLK_LSHIFT: {
      split = false;
      break;
    }
    case SDLK_LCTRL: {
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
    /*
    if (split) {
      // TODO: notify split
      game.splitTiles(coords);
    } else if (merge) {
      // TODO: notify merge
      game.moveTiles(coords);
    }  {
      // TODO: notify move
      game.askMoveTiles(pixel);
    }*/
    if (!move) {
      game.askMoveTiles(pixel);
    }

    if (move) {
      game.moveChessman(last, pixel);
      game.setDefaultBoard();
    } else {
      last(pixel.x(), pixel.y());
    }
    move = !move;
  }
  catch (const ChessException &e) {
    std::cerr << e.what() << std::endl;
  }
}
