#ifndef QUANTUM_CHESS_PROJ_MAIN_DRAWER_H
#define QUANTUM_CHESS_PROJ_MAIN_DRAWER_H

#include "sdl/renderer.h"
#include "game/board.h"
#include "sdl/window.h"

int main_drawer();
void loadWhiteChessmen(Renderer &renderer, Board &board);
void loadChessmen(Renderer &renderer, Board &board);
int game(Window &window, Renderer &renderer);

#endif //QUANTUM_CHESS_PROJ_MAIN_DRAWER_H
