#include "window.h"
#include "renderer.h"
#include "sprite.h"
#include "chessman.h"
#include "board.h"
#include "scene.h"
#include "event_handler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

void loadWhiteChessmen(Renderer &renderer, Board &board);
void loadChessmen(Renderer &renderer, Board &board);
int game(Window &window, Renderer &renderer);

int main() {
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

  loadChessmen(renderer, board); // AUXILIARY FUNCTION
  loadWhiteChessmen(renderer, board); // AUXILIARY FUNCTION

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

void loadWhiteChessmen(Renderer &renderer, Board &board) {
  // begin chessmen
  Position p1(0, 7);
  Chessman tl(renderer, "tw", 100);
  board.createChessman(p1, tl);


  Position p2(1, 7);
  Chessman kl(renderer, "kw", 100);
  board.createChessman(p2, kl);


  Position p3(2, 7);
  Chessman bl(renderer, "bw", 100);
  board.createChessman(p3, bl);


  Position p4(3, 7);
  Chessman q(renderer, "qw", 100);
  board.createChessman(p4, q);


  Position p5(4, 7);
  Chessman k(renderer, "Kw", 100);
  board.createChessman(p5, k);


  Position p6(5, 7);
  Chessman br(renderer, "bw", 100);
  board.createChessman(p6, br);


  Position p7(6, 7);
  Chessman kr(renderer, "kw", 100);
  board.createChessman(p7, kr);

  Position p8(7, 7);
  Chessman tr(renderer, "tw", 100);
  board.createChessman(p8, tr);

  Position p9(0, 6);
  Chessman pwn1(renderer, "pw", 100);
  board.createChessman(p9, pwn1);

  Position p10(1, 6);
  Chessman pwn2(renderer, "pw", 100);
  board.createChessman(p10, pwn2);

  Position p11(2, 6);
  Chessman pwn3(renderer, "pw", 100);
  board.createChessman(p11, pwn3);

  Position p12(3, 6);
  Chessman pwn4(renderer, "pw", 100);
  board.createChessman(p12, pwn4);

  Position p13(4, 6);
  Chessman pwn5(renderer, "pw", 100);
  board.createChessman(p13, pwn5);

  Position p14(5, 6);
  Chessman pwn6(renderer, "pw", 100);
  board.createChessman(p14, pwn6);

  Position p15(6, 6);
  Chessman pwn7(renderer, "pw", 100);
  board.createChessman(p15, pwn7);

  Position p16(7, 6);
  Chessman pwn8(renderer, "pw", 100);
  board.createChessman(p16, pwn8);
  // end chessmen
}

void loadChessmen(Renderer &renderer, Board &board) {
  // begin chessmen
  Position p1(0, 0);
  Chessman tl(renderer, "tb", 100);
  board.createChessman(p1, tl);


  Position p2(1, 0);
  Chessman kl(renderer, "kb", 100);
  board.createChessman(p2, kl);


  Position p3(2, 0);
  Chessman bl(renderer, "bb", 100);
  board.createChessman(p3, bl);


  Position p4(3, 0);
  Chessman q(renderer, "qb", 100);
  board.createChessman(p4, q);


  Position p5(4, 0);
  Chessman k(renderer, "Kb", 100);
  board.createChessman(p5, k);


  Position p6(5, 0);
  Chessman br(renderer, "bb", 100);
  board.createChessman(p6, br);


  Position p7(6, 0);
  Chessman kr(renderer, "kb", 100);
  board.createChessman(p7, kr);

  Position p8(7, 0);
  Chessman tr(renderer, "tb", 100);
  board.createChessman(p8, tr);

  Position p9(0, 1);
  Chessman pwn1(renderer, "pb", 100);
  board.createChessman(p9, pwn1);

  Position p10(1, 1);
  Chessman pwn2(renderer, "pb", 100);
  board.createChessman(p10, pwn2);

  Position p11(2, 1);
  Chessman pwn3(renderer, "pb", 100);
  board.createChessman(p11, pwn3);

  Position p12(3, 1);
  Chessman pwn4(renderer, "pb", 100);
  board.createChessman(p12, pwn4);

  Position p13(4, 1);
  Chessman pwn5(renderer, "pb", 100);
  board.createChessman(p13, pwn5);

  Position p14(5, 1);
  Chessman pwn6(renderer, "pb", 100);
  board.createChessman(p14, pwn6);

  Position p15(6, 1);
  Chessman pwn7(renderer, "pb", 100);
  board.createChessman(p15, pwn7);

  Position p16(7, 1);
  Chessman pwn8(renderer, "pb", 100);
  board.createChessman(p16, pwn8);
  // end chessmen
}
