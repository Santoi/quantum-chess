#include "event_handler.h"
#include "chat/text_entry.h"
#include <iostream>
#include <list>

EventHandler::EventHandler() : split(false), merge(false), move(false) {}

bool EventHandler::handleEvents(Scene &scene, Board &board) {
  PixelCoordinate dest;
  // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        return false;
      }
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE: {
            scene.setDefaultBoard();
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
          if (!scene.isPixelInBoard(pixel))
            break;

          std::list<Position> coords;
          for (size_t i = 0; i < 8; i++) {
            Position pos(0, i);
            coords.push_back(pos);
          }
          if (split) {
            // TODO: notify split
            scene.splitTiles(coords);
          } else if (merge) {
            // TODO: notify merge
            scene.moveTiles(coords);
          } else {
            // TODO: notify move
            scene.moveTiles(coords);
          }

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

bool EventHandler::writeMessage(Renderer &renderer, TextEntry &text_entry) {
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        return false;
      }
      case SDL_TEXTINPUT: {
        text_entry.add(event.text.text);
      }
      case SDL_KEYDOWN: {
        if (event.key.keysym.sym == SDLK_BACKSPACE)
          text_entry.erase();
      }
    }
    renderer.renderer().Clear();
    text_entry.render(240, 240);
    renderer.renderer().Present();
    SDL_Delay(1);
  }
  return true;
}
