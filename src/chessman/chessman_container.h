#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_CONTAINER_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_CONTAINER_H

#include "chessman.h"

class Chessman;
class Board;

/* Contenedor RAII de Chessman. Permite almacenar
 * cualquier objecto heredero de la clase Chessman
 * y obtener su puntero. */
class ChessmanContainer {
    Chessman * pointer;

public:
	/* Constructor, se le pasa la posicion, el color y el tablero.
	 * Ademas se le indica con un char que pieza debe ser:
	 * B (bishop, alfil), K (king, rey), H (knight, caballo),
	 * P (pawn, peon), Q(queen, reina), T (tower, torre). */
    ChessmanContainer(char chessman_, Position position, bool white, Board &board);
    
    // Constructor por movimiento.
    ChessmanContainer(ChessmanContainer && orig);

	// Operador asignacion por movimiento.
    ChessmanContainer & operator=(ChessmanContainer && orig);

	// Devuelve un puntero a la pieza que guarda.
	Chessman * get();

    ChessmanContainer(const ChessmanContainer &) = delete;
    
    ChessmanContainer & operator=(const ChessmanContainer &) = delete;

    ~ChessmanContainer();

    
};


#endif //QUANTUM_CHESS_PROJ_CHESSMAN_CONTAINER_H
