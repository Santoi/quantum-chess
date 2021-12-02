#ifndef QUANTUM_CHESS_PROJ_BOARD_H
#define QUANTUM_CHESS_PROJ_BOARD_H

#include <map>
#include <vector>
#include <stack>
#include <memory>
#include "position.h"
#include "chessman/chessman.h"
#include "pseudo_random_coin.h"
#include "chessman/entanglement_log.h"

#define LOADER_COMMENT '#'

class Chessman;

class ChessmanContainer;

// Represents a chess board, has all the information about the chess match.
class Board {
  std::vector<std::unique_ptr<Chessman>> chessmen;
  std::map<const Position, Chessman *> board;
  bool next_white;
  PseudoRandomCoin coin;
  EntanglementLog entanglement_log;
  bool finished;
  std::stack<std::string> chess_log;

  // Creates a new chessman and returns a smart pointer to it.
  std::unique_ptr<Chessman>
  createChessman(char chessman_, Position position_, bool white_);

public:
  Board();

  // Constructor with random option, splits are random if random if true.
  explicit Board(bool random);

  // Moves chessman from initial to final position. Boolean player_white
  // indicates if player which is playing is white.
  bool move(const Position &initial, const Position &final, bool player_white);
  
  // Split chessman from initial to pos1 and pos2, splitting its probability
  // in a factor 2. Boolean player_white indicates if player which is playing
  // is white.
  void split(const Position &initial, const Position &pos1,
             const Position &pos2, bool player_white);

  // Merge chessman from initial1 and initial2, summing their probability. 
  // Boolean player_white indicates if player which is playing is white.
  void merge(const Position &initial1, const Position &initial2,
             const Position &final, bool player_white);

  std::list<Position> getPossibleMovesOf(const Position &position);
  
  std::list<Position> getPossibleSplitsOf(const Position &position);

  std::list<Position> getPossibleMergesOf(const Position &position);

  std::list<Position>
  getPossibleMergesOf(const Position &position1, const Position &position2);
  
  std::list<Position> getPositionsOf(const Position &position1);

  std::list<Position> getEntangledOf(const Position &position1);

  // Returns a pointer to chessman in position. Returns nullptr if there isnt
  // a chessman.
  Chessman *getChessmanAt(const Position &position);
  
  // Returns true if chessman is in the board (in the map).
  bool isThere(Chessman *chessman);

  // Add a chessman in position given.
  void addChessmanIn(const Position &position, Chessman *chessman);

  // Removes chessman of position,
  void removeChessmanOf(const Position &position);

  /* Quita la pieza de la posicion inicial y la guarda en la
   * posicion inicial. */
  // Remove chessman of initial position and save it in final.
  void addChessmanOfIn(const Position &initial, const Position &final);

  // Loads board with positions given in file.
  void load(std::ifstream &file);

  // Return true if next player to play is white.
  bool isNextWhite() const;

  // Returns a random boolean.
  bool flipACoin();

  void addChessmanOfIn(const Position &initial, const Position &pos1,
                       const Position &pos2);

  // Creates a chessman and add it to position given. chessman_ is chessman
  // name's initial (except for Knight, which is H).
  void addNewChessman(char chessman_, Position position_, bool white_);

  void
  loadVectors(std::vector<char> &characters_, std::vector<bool> &colors_,
              std::vector<Position> &positions_,
              std::vector<double> &probabilities);

  // Finish the game, after calling this methods, no more moves can be done.
  void endGame();
  
  // Push string to log (log is a stack).
  void pushToLog(std::string);

  // Pop strings from log to list (log is a stack).
  void popLog(std::list<std::string> &popped);
};


#endif //QUANTUM_CHESS_PROJ_BOARD_H
