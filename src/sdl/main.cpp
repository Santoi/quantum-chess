#include "window.h"
#include "renderer.h"
#include "sprite.h"
#include "chessman.h"
#include "board.h"
#include "utility.h"
#include "scene.h"
#include "event_handler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

void loadChessmen(Renderer &renderer, Board &board);

int main() {
  SDL2pp::SDL sdl(SDL_INIT_VIDEO);

  Window window;
  Renderer renderer(window);

  Board board;
  Sprite background(renderer, "img/board1.jpg", window.window().GetDrawableHeight(), window.window().GetDrawableHeight());
  Scene scene(renderer.getMinDimension(), board);
  scene.loadSprite(background, 0, 0);
  board.create(renderer);

  loadChessmen(renderer, board); // AUXILIARY FUNCTION

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

void loadChessmen(Renderer &renderer, Board &board) {
  // begin chessmen
  Position p1(0, 0);
  Chessman tl(renderer, 't');
  board.createChessman(p1, tl);


  Position p2(1, 0);
  Chessman kl(renderer, 'k');
  board.createChessman(p2, kl);


  Position p3(2, 0);
  Chessman bl(renderer, 'b');
  board.createChessman(p3, bl);


  Position p4(3, 0);
  Chessman q(renderer, 'q');
  board.createChessman(p4, q);


  Position p5(4, 0);
  Chessman k(renderer, 'K');
  board.createChessman(p5, k);


  Position p6(5, 0);
  Chessman br(renderer, 'b');
  board.createChessman(p6, br);


  Position p7(6, 0);
  Chessman kr(renderer, 'k');
  board.createChessman(p7, kr);

  Position p8(7, 0);
  Chessman tr(renderer, 't');
  board.createChessman(p8, tr);
  // end chessmen
}
