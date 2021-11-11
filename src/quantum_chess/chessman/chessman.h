#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H

#include <vector>
#include <string>
#include "../position.h"
#include "../board.h"
#include "../quantum_position.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

// TODO CHEQUEAR SI TODOS LOS QUE ESTAN EN EL MEDIO SUMAN 100 % PROBA.

class Board;
class ChessmanContainer;
class QuantumPosition;

/* Clase abstracta que representa una pieza del tablero.
 * Posee como atributos una COMPLETAR de posiciones, una
 * referencia al tablero al que pertenece y un booleano
 * que indica color. */
class Chessman {
    Chessman();
    bool measured;

protected:
    std::list<QuantumPosition> positions;
    Board & board;
    bool white;

	/* Calcula los casilleros por los que se debe pasar para llegar desde
	 * una posicion a otra. No asegura orden, solo que la posicion
	 * final se encuentra al final del vector. */
    virtual void calculatePath(const Position &initial,
                               const Position &final,
                               std::vector<Position> &path) const;

	// Calcula camino por una fila.
    void calculateFilePath(const Position &initial,
                           const Position &final,
                           std::vector<Position> &path) const;

	// Calcula camino por una columna.
    void calculateRowPath(const Position &initial,
                          const Position &final,
                          std::vector<Position> &path) const;

	// Calcula camino por una diagonal.
    void calculateDiagonalPath(const Position &initial,
                               const Position &final,
                               std::vector<Position> &path) const;

    /* Devuelve si el camino es transitable (hay como mucho una pieza cuantica
     * en el trayecto. Guarda en el puntero la pieza. No chequea ni la primer
     * ni ultima posicion. */
    bool getMiddlePathChessman(const std::vector<Position> &path,
                               std::pair<Position, Chessman *>  & chessman) const;

	// Chequea que el camino sea transitable.
    bool checkFreePath(const std::vector<Position> & path) const;

	/* Chequea si el movimiento se puede realizar y carga un vector con las
	 * piezas que hay en el trayecto de haberlos. */
    void checkCanMoveOrFail(const Position & initial, const Position & final) const;

	// Metodo que devuelve la letra que representa a la pieza.
    virtual std::string print() const = 0;

public:
	// Constructor, se le pasa posicion, color y referencia al tablero.
    Chessman(const Position & position_, bool white_, Board & board_);

	// Mueve la pieza desde una posicion a otra, valida el movimiento.
    virtual void move(const Position & initial, const Position & final);

    void merge(const Position &initial1, const Position &initial2,
               const Position &final);

	// Devuelve true si la pieza esta en estado cuantico.
    bool isQuantum() const;

	// Devuelve true si la pieza es blanca.
	bool isWhite() const;

    // Devuelve la posicion real de una pieza.
    const QuantumPosition & getPosition() const;

    // Devuelve las posiciones falsas de la pieza
    std::list<QuantumPosition> & getAllPositions();

    // Carga un vector con todos las posiciones a donde se puede mover la pieza.
    virtual void calculatePosibleMoves(const Position &initial,
                                       std::vector<Position> &posible_moves)
                                       const = 0;
	
    friend std::ostream & operator<<(std::ostream & os,
                                     const Chessman & chessman);

    virtual ~Chessman() = default;

    void split(const Position &initial, const Position &position1,
               const Position &position2);

    double getProbability(Position position);

    void measure(const Position &position);

    void
    entangle(const Position &position, Chessman &other, const Position &other_position);

    void measureOthers(QuantumPosition & quantum_position);

    bool entangledPositionAppearsMoreThanOnce(QuantumPosition * position);

    void resetMeasured();

    const QuantumPosition &getPosition(size_t index) const;

    size_t positionsSize() const;

    std::list<QuantumPosition *>
    searchAppearsInAllLessIn(QuantumPosition &quantumPosition);
};

#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
