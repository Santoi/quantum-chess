#include "event_handler.h"
#include <iostream>

EventHandler::EventHandler(): split(false), merge(false), move(false) {}

bool EventHandler::handleEvents(Scene &scene, Board &board) {
  PixelCoordinate dest;
  // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
  while(SDL_PollEvent(&event)){
    switch(event.type) {
      case SDL_QUIT: {
        return false;
      }
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE: {
            scene.setDefaultBoard();
            break;
          }
          case SDLK_RSHIFT: case SDLK_LSHIFT: {
            split = true;
            break;
          }
          case SDLK_LCTRL: {
            merge = true;
            break;
          }
          case SDLK_q: // TODO: temporary
            return false;
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
          if (split) {
            // TODO: notify split
          } else if (merge) {
            // TODO: notify merge
          }
          scene.moveTiles(pixel);
          if (move) {
            scene.moveChessman(last, pixel);
            scene.setDefaultBoard();
          } else {
            last(pixel.x(), pixel.y());
          }
          move = !move;
        }
        break;
      }
    }
  }
  return true;
}
