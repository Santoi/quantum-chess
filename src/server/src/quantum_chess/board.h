#ifndef QUANTUM_CHESS_PROJ_BOARD_H
#define QUANTUM_CHESS_PROJ_BOARD_H

#include <map>
#include <vector>
#include <memory>
#include "position.h"
#include "chessman/chessman.h"
#include "pseudo_random_coin.h"

class Chessman;

class ChessmanContainer;

/* Clase que representa al tablero, tiene como atributos
 * los contenedores de las piezas, un mapa donde las
 * guarda segun posiciones y un booleano para indicar el 
 * turno. */
class Board {
  std::vector<std::unique_ptr<Chessman>> chessmen;
  std::map<const Position, Chessman *> board;
  bool next_white;
  PseudoRandomCoin coin;


  std::unique_ptr<Chessman>
  createChessman(char chessman_, Position position_, bool white_);

public:
  Board();

  explicit Board(int seed);

  /* Mueve la pieza en la posicion inicial a la final, validando
   * el movimiento. */
  void move(const Position &initial, const Position &final, bool player_white);

  void split(const Position &initial, const Position &pos1,
             const Position &pos2, bool player_white);

  std::list<Position> getPossibleMovesOf(const Position &position);

  // Devuelve un puntero a la pieza en la posicion dada.
  Chessman *getChessmanAt(const Position &position);

  // Quita la pieza de la posicion dada.
  void removeChessmanOf(const Position &position);

  /* Quita la pieza de la posicion inicial y la guarda en la
   * posicion inicial. */
  void addChessmanOfIn(const Position &initial, const Position &final);

  // Carga el tablero con las posiciones iniciales del ajedrez.
  void load();

  // Devuelve true si el siguiente turno es de las blancas.
  bool isNextWhite() const;

  bool flipACoin();

  void addChessmanOfIn(const Position &initial, const Position &pos1,
                       const Position &pos2);

  void addChessmanIn(const Position &position, Chessman *chessman);

  void merge(const Position &initial1, const Position &initial2,
             const Position &final);

  bool isThere(Chessman *chessman);

  void addNewChessman(char chessman_, Position position_, bool white_);

  void
  loadVectors(std::vector<char> &characters_, std::vector<bool> &colors_,
              std::vector<Position> &positions_,
              std::vector<double> &probabilities);

  std::list<Position> getPossibleSplitsOf(const Position &position);

  std::list<Position> getPossibleMergesOf(const Position &position);

  std::list<Position>
  getPossibleMergesOf(const Position &position1, const Position &position2);

  std::list<Position> getPositionsOf(const Position &position1);

  std::list<Position> getEntangledOf(const Position &position1);
};


#endif //QUANTUM_CHESS_PROJ_BOARD_H
