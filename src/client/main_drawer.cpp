#include "main_drawer.h"
#include "sdl/window.h"
#include "sdl/renderer.h"
#include "sdl/sprite.h"
#include "game/chessman.h"
#include "game/board.h"
#include "sdl/scene.h"
#include "sdl/event_handler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

// TODO: drawer thread
int main_drawer() {
  SDL2pp::SDL sdl(SDL_INIT_VIDEO);

  Window window;
  Renderer renderer(window);
  game(window, renderer);
  return 0;
}

int game(Window &window, Renderer &renderer) {
  Board board(renderer,
              "img/stars.jpg",
              renderer.getMinDimension(),
              renderer.getMinDimension());
  Scene scene(renderer.getMinDimension(), board);

  unsigned int prev_ticks = SDL_GetTicks();

  EventHandler eventHandler;
  bool running = true;
  // Main loop
  while (running) {
    // Timing: calculate difference between this and previous frame
    // in milliseconds
    unsigned int frame_ticks = SDL_GetTicks();
    unsigned int frame_delta = frame_ticks - prev_ticks;
    prev_ticks = frame_ticks;

    running = eventHandler.handleEvents(scene, board);

    // Show rendered frame
    renderer.render(scene);

    // Frame limiter: sleep for a little bit to not eat 100% of CPU
    SDL_Delay(1);
  }
  return 0;
}
