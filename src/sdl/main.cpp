#include "sprite.h"
#include "chessman.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#define DEFAULT_HEIGHT 480
#define DEFAULT_WIDTH 640

int main() {
  SDL2pp::SDL sdl(SDL_INIT_VIDEO);

  // Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
  SDL2pp::Window window("SDL2pp demo",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                DEFAULT_WIDTH, DEFAULT_HEIGHT,
                SDL_WINDOW_RESIZABLE);

  // Create accelerated video renderer with default driver
  SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

  Sprite board(renderer, "img/board1.jpg");
  Chessman tower(renderer, 't');
  Chessman falcon(renderer, 'f');
  Chessman bishop(renderer, 'b');


  // Main loop
  while (true) {
    // Event processing:
    // - If window is closed, or Q or Escape buttons are pressed,
    //   quit the application
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return 0;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE: case SDLK_q:
            return 0;
        }
      }
    }

    int height = renderer.GetOutputHeight();

    renderer.Clear();

    board.render(0, 0, height, height);
    tower.drawAt(0, 0);
    falcon.drawAt(7, 7);
    bishop.drawAt(2, 0);

    // Show rendered frame
    renderer.Present();

    // Frame limiter: sleep for a little bit to not eat 100% of CPU
    SDL_Delay(1);
  }
  return 0;
}
