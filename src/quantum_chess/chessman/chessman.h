#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H

#include <vector>
#include <list>
#include <utility>
#include <string>
#include "../position.h"
#include "../board.h"
#include "../quantum_position.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

class Board;
class ChessmanContainer;
class QuantumPosition;

/* Clase abstracta que representa una pieza del tablero.
 * Posee como atributos una COMPLETAR de posiciones, una
 * referencia al tablero al que pertenece y un booleano
 * que indica color. */
class Chessman {
    friend class QuantumPosition;
protected:
    typedef enum {
        OK,
        CHESSMAN_NOT_IN_POSITION,
        MOVING_TO_SQUARE_WITH_SAME_PIECE,
        MEASURING_AND_ENTANGLING,
        ENTANGLING_SAME_PIECE_TWO_TIMES,
        MOVING_TO_SAME_SQUARE,
        NON_FREE_PATH,
        SPLIT_TO_OCCUPIED_SQUARE,
        SPLITTING_AND_ENTANGLING,
        SPLIT_LIMIT_REACHED,
        MERGING_AND_ENTANGLING,
        PAWN_CANT_SPLIT,
        PAWN_CANT_MERGE,
        PAWN_CANT_ENTANGLE
    } MoveValidationStatus;

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
                               std::pair<Position,
                               Chessman *>  & chessman) const;

	// Chequea que el camino sea transitable.
    bool checkFreePath(const std::vector<Position> &path, std::pair<Position,
            Chessman *> &chessman_in_path, bool final_same_color_free) const;

	// Metodo que devuelve la letra que representa a la pieza.
    virtual std::string print() const = 0;

    std::list<QuantumPosition *>
    searchEntangledWithAllPositionsExceptWith(const QuantumPosition &
                                              filtered_qp);

    bool chessmanIsAlreadyEntangled(Chessman * chessman);

    void checkIsInBoardOrFail(const Position &position);

    void entangle(const Position & initial, const Position & final,
                  Chessman & other, const Position &other_position);

    void measureOthers(QuantumPosition & quantum_position);

    bool entangledPositionAppearsMoreThanOnce(QuantumPosition * position);

    virtual
    MoveValidationStatus checkIsAValidMove(const Position &initial,
                                           const Position &final);

    virtual Chessman::MoveValidationStatus
    checkIsAValidSplit(const Position &initial, const Position &final);

    virtual Chessman::MoveValidationStatus
    checkIsAValidMerge(const Position &initial1, const Position &final);

public:
	// Constructor, se le pasa posicion, color y referencia al tablero.
    Chessman(const Position & position_, bool white_, Board & board_);

	// Mueve la pieza desde una posicion a otra, valida el movimiento.
    virtual void move(const Position & initial, const Position & final);

    void split(const Position &initial, const Position &final1,
               const Position &final2);

    void merge(const Position &initial1, const Position &initial2,
               const Position &final);

	// Devuelve true si la pieza esta en estado cuantico.
    bool isQuantum() const;

	// Devuelve true si la pieza es blanca.
	bool isWhite() const;

    // Carga un vector con todos las posiciones a donde se puede mover la pieza.
    virtual void calculateMoves(const Position &initial,
                                std::vector<Position> &posible_moves)
                                       const = 0;
	
    friend std::ostream & operator<<(std::ostream & os,
                                     const Chessman & chessman);

    virtual ~Chessman() = default;

    double getProbability(Position position);

    // Devuelve la posicion real de una pieza.
    const QuantumPosition & getPosition() const;

    const QuantumPosition & getPosition(size_t index) const;

    size_t countPositions() const;

    // TODO despues hacer privada.
    void measure(const Position &position);

    void moveValidationExceptionThrower(MoveValidationStatus status);

    virtual void calculatePosibleMoves(const Position &initial,
                               std::vector<Position> &posible_moves);

    virtual void calculatePosibleSplits(const Position &initial,
                                std::vector<Position> &posible_moves);

    virtual void calculatePosibleMerges(const Position &initial,
                                std::vector<Position> &posible_moves);
};

#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
