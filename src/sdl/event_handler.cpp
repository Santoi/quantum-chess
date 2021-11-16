#include "event_handler.h"

bool handleEvents(Scene &scene, Board &board) {
  SDL_Event event;
  // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
  while(SDL_PollEvent(&event)){
    switch(event.type) {
      case SDL_QUIT: {
        return false;
      }
      case SDL_KEYDOWN: {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            scene.setDefaultBoard();
            break;
          case SDLK_q:
            return false;
        }
      }
      case SDL_MOUSEBUTTONDOWN: {
        // handleMouseEvent(event.button) function
        SDL_MouseButtonEvent mouse = event.button;
        if (mouse.button == SDL_BUTTON_LEFT) {
          PixelCoordinate pixel(mouse.x, mouse.y);
          scene.moveTiles(pixel);
        }
      }
    }
  }
  return true;
}
