#ifndef QUANTUM_CHESS_PROJ_BOARD_H
#define QUANTUM_CHESS_PROJ_BOARD_H

#include <map>
#include <vector>
#include <stack>
#include <memory>
#include <string>
#include <list>
#include "position.h"
#include "chessman/chessman.h"
#include "pseudo_random_coin.h"
#include "chessman/entanglement_log.h"
#include "client_data.h"

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

  // Creates a new chessman_ and returns a smart pointer to it.
  std::unique_ptr<Chessman>
  createChessman(char chessman_, Position position_, bool white_);

public:
  Board();

  // Constructor with random option, splits are random if random if true.
  explicit Board(bool random);

  // Moves chessman_ from initial to final position. Boolean player_white
  // indicates if player which is playing is white.
  bool move(const Position &initial, const Position &final, bool player_white);

  // Split chessman_ from initial to pos1 and pos2, splitting its probability
  // in a factor 2. Boolean player_white indicates if player which is playing
  // is white.
  void split(const Position &initial, const Position &pos1,
             const Position &pos2, bool player_white);

  // Merge chessman_ from initial1 and initial2, summing their probability.
  // Boolean player_white indicates if player which is playing is white.
  void merge(const Position &initial1, const Position &initial2,
             const Position &final, bool player_white);

  // Loads in output possible moves of chessman_ in position.
  void getPossibleMovesOf(const Position &position,
                          std::list<Position> &output);

  // Loads in output possible splits of chessman_ in position.
  void getPossibleSplitsOf(const Position &position,
                           std::list<Position> &output);

  // Loads in output possible merges of chessman_ in position.
  void getPossibleMergesOf(const Position &position,
                           std::list<Position> &output);

  // Loads in output possible merges of two chessman_ in position
  // (possible moves that share both).
  void
  getPossibleMergesOf(const Position &position1, const Position &position2,
                      std::list<Position> &output);

  // Loads in output all positions of chessman_.
  void getPositionsOf(const Position &position1, std::list<Position> &output);

  // Loads in output all positions of entangled chessmen with chessman_ in
  // position.
  void
  getEntangledOf(const Position &position1, std::list<Position> &output);

  // Returns a pointer to chessman_ in position. Returns nullptr if there isn't
  // a chessman_.
  Chessman *getChessmanAt(const Position &position);

  // Returns true if chessman_ is in the board (in the map).
  bool isThere(Chessman *chessman);

  // Add a chessman_ in position given.
  void addChessmanIn(const Position &position, Chessman *chessman);

  // Removes chessman_ of position,
  void removeChessmanOf(const Position &position);

  // Remove chessman_ of initial position and save it in final.
  void addChessmanOfIn(const Position &initial, const Position &final);

  // Loads board with positions given in file.
  void load(std::ifstream &file);

  // Return true if next player to play is white.
  bool isNextWhite() const;

  // Returns a random boolean.
  bool flipACoin();

  // Creates a chessman_ and add it to position given. chessman_ is chessman_
  // name's initial (except for Knight, which is H).
  void addNewChessman(char chessman_, Position position_, bool white_);

  void
  loadVectorOfSquareData(std::vector<SquareData> &data);

  // Finish the game, after calling this methods, no more moves can be done.
  void endGame();

  // Push string to log (log is a stack).
  void pushToLog(std::string);

  // Pop strings from log to list (log is a stack).
  void popLog(std::list<std::string> &popped);
};


#endif //QUANTUM_CHESS_PROJ_BOARD_H
