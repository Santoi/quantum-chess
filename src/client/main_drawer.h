#ifndef QUANTUM_CHESS_PROJ_MAIN_DRAWER_H
#define QUANTUM_CHESS_PROJ_MAIN_DRAWER_H

#include "../common/src/blocking_queue.h"
#include "communication/remote_client_instructions.h"
#include "sdl/renderer.h"
#include "game/client_board.h"
#include "sdl/window.h"

int main_drawer(BlockingQueue<RemoteClientInstruction> &send_queue);
void loadWhiteChessmen(Renderer &renderer, Board &board);
void loadChessmen(Renderer &renderer, Board &board);
int game(Window &window, Renderer &renderer, BlockingQueue<RemoteClientInstruction> &send_queue);

#endif //QUANTUM_CHESS_PROJ_MAIN_DRAWER_H
