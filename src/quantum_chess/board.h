#ifndef QUANTUM_CHESS_PROJ_BOARD_H
#define QUANTUM_CHESS_PROJ_BOARD_H

#include <map>
#include "position.h"
#include "chessman/chessman.h"
#include "chessman/chessman_container.h"
#include <vector>

class Chessman;
class ChessmanContainer;

/* Clase que representa al tablero, tiene como atributos
 * los contenedores de las piezas, un mapa donde las
 * guarda segun posiciones y un booleano para indicar el 
 * turno. */
class Board {
    std::vector<ChessmanContainer> chessmen;
    std::map<const Position, Chessman *> board;
    bool next_white;

public:
    Board();

	/* Mueve la pieza en la posicion inicial a la final, validando
	 * el movimiento. */
    void move(const Position & initial, const Position & final);

	// Devuelve un puntero a la pieza en la posicion dada.
    Chessman * getChessmanAt(const Position & position);

	// Quita la pieza de la posicion dada.
    void removeChessmanOf(const Position &position);

	/* Quita la pieza de la posicion inicial y la guarda en la
	 * posicion inicial. */
    void addChessmanOfIn(const Position &initial, const Position &final);

	// Carga el tablero con las posiciones iniciales del ajedrez.
    void load();

	/* Agrega una pieza en el vector contenedor y en su posicion
	 * en el map. */
    void addChessman(ChessmanContainer &&chessman_cont);

	// Devuelve true si el siguiente turno es de las blancas.
    bool isNextWhite() const;
};


#endif //QUANTUM_CHESS_PROJ_BOARD_H
