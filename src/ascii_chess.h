#ifndef QUANTUM_CHESS_PROJ_ASCII_CHESS_H
#define QUANTUM_CHESS_PROJ_ASCII_CHESS_H

#include "board.h"

// Clase que ejecuta el ajedrez en formato ASCII.
class AsciiChess {
    Board board;
    
    // Dibuja el tablero.
    void draw();

	// Lee comandos de entrada.
    bool readCommand();

public:
    AsciiChess();
    
    // Ejecuta el juego.
    void execute();
};


#endif //QUANTUM_CHESS_PROJ_ASCII_CHESS_H
