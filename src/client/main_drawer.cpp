#include "main_drawer.h"
#include "sdl/window.h"
#include "sdl/renderer.h"
#include "sdl/sprite.h"
#include "game/chessman.h"
#include "game/board.h"
#include "game/game.h"
#include "sdl/event_handler_thread.h"
#include "../common/src/blocking_queue.h"
#include "communication/remote_client_instructions.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

// TODO: drawer thread
int main_drawer(BlockingQueue<RemoteClientInstruction> &send_queue) {
  SDL2pp::SDL sdl(SDL_INIT_VIDEO);

  Window window;
  Renderer &renderer = window.renderer();
  game(window, renderer, send_queue);
  return 0;
}

int game(Window &window, Renderer &renderer, BlockingQueue<RemoteClientInstruction> &send_queue) {
  Game game(window, send_queue);

  unsigned int prev_ticks = SDL_GetTicks();
  bool running = true;
  // Main loop
  while (running) {
    // Timing: calculate difference between this and previous frame
    // in milliseconds
    unsigned int frame_ticks = SDL_GetTicks();
    unsigned int frame_delta = frame_ticks - prev_ticks;
    prev_ticks = frame_ticks;

    //running = eventHandler.run(game);

    // Show rendered frame
    renderer.render(game);

    // Frame limiter: sleep for a little bit to not eat 100% of CPU
    SDL_Delay(1);
  }
  return 0;
}
