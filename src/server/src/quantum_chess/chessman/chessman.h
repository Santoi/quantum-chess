#ifndef QUANTUM_CHESS_PROJ_CHESSMAN_H
#define QUANTUM_CHESS_PROJ_CHESSMAN_H

#include <vector>
#include <list>
#include <utility>
#include <string>
#include "../position.h"
#include "../board.h"
#include "../quantum_position.h"
#include "entanglement_log.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

class Board;

class ChessmanContainer;

class QuantumPosition;

// Abstract class that represent a chessman or quantum chessman.
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
    PAWN_CANT_ENTANGLE,
    PAWN_CANT_EAT_LIKE_THAT
  } MoveValidationStatus;

  std::list<QuantumPosition> positions;
  Board &board;
  bool white;
  EntanglementLog &entanglement_log;

  // Calculates squares where chessman has to pass to go from one position to
  // another. It doesn't secures order, only that last position is in final
  // position of the vector.
  virtual void calculatePath(const Position &initial,
                             const Position &final,
                             std::vector<Position> &path) const;

  // Calculates path by a row.
  void calculateFilePath(const Position &initial,
                         const Position &final,
                         std::vector<Position> &path) const;

  // Calculates path by a column.
  void calculateRowPath(const Position &initial,
                        const Position &final,
                        std::vector<Position> &path) const;

  // Calculates path by a diagonal.
  void calculateDiagonalPath(const Position &initial,
                             const Position &final,
                             std::vector<Position> &path) const;

  // Returns true if path can be walked (there is at the most one quantum
  // chessman) and saves a pointer to the chessman in a pair with its position.
  // Doesnt' check last position.
  bool getMiddlePathChessman(const std::vector<Position> &path,
                             std::pair<Position,
                                     Chessman *> &chessman) const;

  // Returns true if path can be walked. It checks last position, and boolean
  // final_same_color_free states if it's ok to be a chessman of same color
  // or different color in the final position.
  bool checkFreePath(const std::vector<Position> &path, std::pair<Position,
          Chessman *> &chessman_in_path, bool final_same_color_free) const;

  // Returns true if chessman is already entangled.
  bool chessmanIsAlreadyEntangled(Chessman *chessman);

  // Checks if chessman is in board. If not, it throws exception.
  void checkIsInBoardOrFail(const Position &position);

  // Measure other chessman entangled with QuantumPosition.
  void measureOthers(QuantumPosition &quantum_position);

  // Checks if a move is valid. Returning a status. It is used for validating
  // possible moves and moves send by user.
  virtual
  MoveValidationStatus checkIsAValidMove(const Position &initial,
                                         const Position &final);
  // Checks if a split is valid. Returning a status. It is used for validating
  // possible splits and splits send by user.
  virtual Chessman::MoveValidationStatus
  checkIsAValidSplit(const Position &initial, const Position &final);

  // Checks if a merge is valid. Returning a status. It is used for validating
  // possible merges and merges send by user.
  virtual Chessman::MoveValidationStatus
  checkIsAValidMerge(const Position &initial1, const Position &final);

  // Loads a vector with all posible moves of the chessman.
  virtual void calculateMoves(const Position &initial,
                              std::list<Position> &posible_moves) const = 0;

  // Depending on status passed, throws an exception with corresponding message.
  void moveValidationExceptionThrower(MoveValidationStatus status);

  // Entangles chessman with the other chessman. Splitting this chessman with
  // corresponding probability.
  void entangle(const Position &initial, const Position &final,
                Chessman &other, const Position &other_position);

public:
  Chessman(const Position &position_, bool white_, Board &board_,
           EntanglementLog &entanglement_log_);
           
  virtual ~Chessman() = default;
           
  // Moves chessman from initial position to final, validating the move.
  virtual bool move(const Position &initial, const Position &final);

  // Splits chessman from initial position to final1 and final2 validating.
  virtual void split(const Position &initial, const Position &final1,
                     const Position &final2);
  
  // Merges chessman from initial1 and initial2 to final, validating.
  void merge(const Position &initial1, const Position &initial2,
             const Position &final);

  // Returns true if chessman is in quantum state.
  bool isQuantum() const;

  // Returns true is chessman is white. 
  bool isWhite() const;

  friend std::ostream &operator<<(std::ostream &os,
                                  const Chessman &chessman);

  // Returns probability corresponding to position.
  double getProbability(Position position);

  // Returns real position of chessman.
  const QuantumPosition &getPosition() const;

  // Returns position of index.
  const QuantumPosition &getPosition(size_t index) const;

  // Returns amount of positions of chessman.
  size_t countPositions() const;

  // TODO despues hacer privada.
  // Measures position of chessman.
  void measure(const Position &position);

  // Calculates possible moves of chessman from initial position.
  virtual void calculatePossibleMoves(const Position &initial,
                                      std::list<Position> &posible_moves);

  // Calculates possible splits of chessman from initial position.
  virtual void calculatePossibleSplits(const Position &initial,
                                       std::list<Position> &posible_moves);
  
  // Calculates possible merges of chessman from initial position.
  virtual void calculatePossibleMerges(const Position &initial,
                                       std::list<Position> &posible_moves);

  // Calculates possible merges of chessman from two initial positions. Only
  // is a merge possible if it possible for the two initial positions.
  void
  calculatePossibleMerges(const Position &initial1, const Position &initial2,
                          std::list<Position> &posible_moves);
                          
  // Load list with all the positions of chessman.
  void getAllPositions(std::list<Position> &output) const;

  // Load list with all positions of all entangled chessman.
  void getEntangledPositions(std::list<Position> &output);

  // Returns character that represents chessman.
  virtual char charId() const = 0;
};

#endif //QUANTUM_CHESS_PROJ_CHESSMAN_H
