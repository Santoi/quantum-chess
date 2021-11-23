#include "event_handler_thread.h"
#include <iostream>
#include <list>

EventHandlerThread::EventHandlerThread(Game &game) : open(true), game(game),
                                                     split(false), merge(false),
                                                     move(false) {}

void EventHandlerThread::run() {
  // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
  while (true) {
    if (!SDL_PollEvent(&event))
      continue;
    switch (event.type) {
      case SDL_QUIT: {
        open = false;
        return;
      }
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE: {
            game.setDefaultBoard();
            move = false;
            break;
          }
          case SDLK_RSHIFT:
          case SDLK_LSHIFT: {
            split = true;
            break;
          }
          case SDLK_LCTRL: {
            merge = true;
            break;
          }
          case SDLK_q: // TODO: temporary
            open = false;
            return;
        }
        break;
      }
      case SDL_KEYUP: {
        switch (event.key.keysym.sym) {
          case SDLK_RSHIFT:
          case SDLK_LSHIFT: {
            split = false;
            break;
          }
          case SDLK_LCTRL: {
            merge = false;
            break;
          }
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN: {
        // handleMouseEvent(event.button) function
        SDL_MouseButtonEvent mouse = event.button;
        if (mouse.button == SDL_BUTTON_LEFT) {
          PixelCoordinate pixel(mouse.x, mouse.y);
          if (!game.isPixelInBoard(pixel))
            break;

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
        break;
      }
    }
  }
}

bool EventHandlerThread::isOpen() {
  return open;
}
