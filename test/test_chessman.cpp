#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include "../src/server/src/quantum_chess/board.h"
#include "../src/server/src/quantum_chess/chessman/tower.h"
#include "../src/server/src/quantum_chess/chessman/tower.h"
#include "../src/server/src/quantum_chess/chessman/bishop.h"
#include "../src/server/src/quantum_chess/chessman/king.h"
#include "../src/common/src/chess_exception.h"


TEST(Chessman, MoveFromANonExistingPosition) {
  Board board;
  board.addNewChessman('T', Position(0, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(0, 1));

  EXPECT_THROW(chessman->move(Position(0, 2),
                              Position(0, 3)), ChessException);
}

TEST(Chessman, ClassicToClassicCapture) {
  Board board;
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), false);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  bishop->move(Position(0, 0), Position(1, 1));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(1, 1, 1));
  EXPECT_FALSE(board.isThere(queen));
}

TEST(Chessman, MoveThenMove) {
  Board board;
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));

  queen->move(Position(1, 1), Position(2, 2));
  EXPECT_EQ(queen->getPosition(), QuantumPosition(2, 2, 1));

  queen->move(Position(2, 2), Position(3, 3));
  EXPECT_EQ(queen->getPosition(), QuantumPosition(3, 3, 1));
}

TEST(Tower, CalculatePosibleMovesWithEmptyBoard) {
  Board board;
  board.addNewChessman('T', Position(5, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(5, 1));

  std::list<Position> posible_moves;

  chessman->calculatePossibleMoves(Position(5, 1), posible_moves);

  std::list<Position> posible_moves_gt = {
          Position(5, 0), Position(5, 2),
          Position(5, 3), Position(5, 4),
          Position(5, 5), Position(5, 6),
          Position(5, 7), Position(0, 1),
          Position(1, 1), Position(2, 1),
          Position(3, 1), Position(4, 1),
          Position(6, 1), Position(7, 1),
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Tower, MoveWithEmptyBoard) {
  Board board;
  board.addNewChessman('T', Position(5, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(5, 1));

  chessman->move(Position(5, 1), Position(5, 3));
  chessman->move(Position(5, 3), Position(1, 3));

  EXPECT_EQ(Position(1, 3), chessman->getPosition());
}

TEST(Tower, MoveWithChessmanInTheBoard) {
  Board board;
  board.addNewChessman('T', Position(5, 1), true);
  Chessman *tower = board.getChessmanAt(Position(5, 1));
  board.addNewChessman('T', Position(7, 3), true);

  tower->move(Position(5, 1), Position(7, 1));

  EXPECT_EQ(Position(7, 1), tower->getPosition());

  tower->move(Position(7, 1), Position(7, 2));
  EXPECT_EQ(Position(7, 2), tower->getPosition());
}

TEST(Tower, BadMoveToChessmanSameColorPosition) {
  Board board;
  board.addNewChessman('T', Position(5, 1), true);
  Chessman *tower = board.getChessmanAt(Position(5, 1));
  board.addNewChessman('T', Position(7, 1), true);

  EXPECT_THROW(tower->move(Position(5, 1), Position(7, 1)),
               ChessException);
}

TEST(Tower, MoveToChessmanDiffColorPosition) {
  Board board;
  board.addNewChessman('T', Position(5, 1), true);
  Chessman *tower = board.getChessmanAt(Position(5, 1));
  board.addNewChessman('T', Position(7, 1), false);

  tower->move(Position(5, 1), Position(7, 1));

  EXPECT_EQ(Position(7, 1), tower->getPosition());
}

TEST(Tower, BadMoveWithChessmanInTheMiddle) {
  Board board;
  board.addNewChessman('T', Position(7, 1), true);
  Chessman *tower = board.getChessmanAt(Position(7, 1));
  board.addNewChessman('T', Position(7, 3), true);

  EXPECT_THROW(tower->move(Position(7, 1), Position(7, 5)),
               ChessException);
}

TEST(Tower, BadMoveWithEmptyBoard) {
  Board board;
  board.addNewChessman('T', Position(5, 1), true);
  Chessman *tower = board.getChessmanAt(Position(5, 1));

  EXPECT_THROW(tower->move(Position(5, 1), Position(2, 3)),
               ChessException);
}

// Se testea el alfil para probar el movimiento diagonal
TEST(Bishop, CalculatePosibleMovesWithEmptyBoard) {
  Board board;
  board.addNewChessman('B', Position(2, 1), true);
  Chessman *bishop = board.getChessmanAt(Position(2, 1));

  std::list<Position> posible_moves;

  bishop->calculatePossibleMoves(Position(2, 1), posible_moves);

  std::list<Position> posible_moves_gt = {
          Position(1, 0), Position(3, 2),
          Position(4, 3), Position(5, 4),
          Position(6, 5), Position(7, 6),
          Position(3, 0), Position(1, 2),
          Position(0, 3)
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Bishop, MoveWithEmptyBoard) {
  Board board;
  board.addNewChessman('B', Position(7, 7), true);
  Chessman *bishop = board.getChessmanAt(Position(7, 7));

  bishop->move(Position(7, 7), Position(4, 4));
  bishop->move(Position(4, 4), Position(1, 7));

  EXPECT_EQ(Position(1, 7), bishop->getPosition());
}

TEST(Bishop, MoveWithChessmanInTheBoard) {
  Board board;
  board.addNewChessman('T', Position(7, 3), true);
  board.addNewChessman('B', Position(5, 1), true);

  Chessman *bishop = board.getChessmanAt(Position(5, 1));

  bishop->move(Position(5, 1), Position(6, 2));

  EXPECT_EQ(Position(6, 2), bishop->getPosition());

  bishop->move(Position(6, 2), Position(5, 3));
  EXPECT_EQ(Position(5, 3), bishop->getPosition());
}

TEST(Bishop, BadMoveToChessmanSameColorPosition) {
  Board board;
  board.addNewChessman('T', Position(7, 7), true);
  board.addNewChessman('B', Position(5, 5), true);

  Chessman *bishop = board.getChessmanAt(Position(5, 5));

  EXPECT_THROW(bishop->move(Position(5, 5), Position(7, 7)), ChessException);
}

TEST(Bishop, MoveToChessmanDiffColorPosition) {
  Board board;
  board.addNewChessman('T', Position(0, 1), false);
  board.addNewChessman('B', Position(1, 0), true);

  Chessman *bishop = board.getChessmanAt(Position(1, 0));

  bishop->move(Position(1, 0), Position(0, 1));

  EXPECT_EQ(Position(0, 1), bishop->getPosition());
}

TEST(Bishop, BadMoveWithChessmanInTheMiddle) {
  Board board;
  board.addNewChessman('T', Position(6, 3), true);
  board.addNewChessman('B', Position(7, 2), true);

  Chessman *bishop = board.getChessmanAt(Position(7, 2));

  EXPECT_THROW(bishop->move(Position(7, 2), Position(5, 4)),
               ChessException);
}

TEST(Bishop, BadMoveWithEmptyBoard) {
  Board board;
  board.addNewChessman('B', Position(5, 1), true);

  Chessman *bishop = board.getChessmanAt(Position(5, 1));

  EXPECT_THROW(bishop->move(Position(5, 1), Position(5, 2)),
               ChessException);
}

TEST(King, CalculatePosibleMovesWithEmptyBoard) {
  Board board;
  board.addNewChessman('K', Position(2, 1), true);
  Chessman *king = board.getChessmanAt(Position(2, 1));

  std::list<Position> posible_moves;

  king->calculatePossibleMoves(Position(2, 1), posible_moves);

  std::list<Position> posible_moves_gt = {
          Position(3, 1), Position(3, 2),
          Position(2, 2), Position(1, 2),
          Position(1, 1), Position(1, 0),
          Position(2, 0), Position(3, 0)
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Knight, CalculatePosibleMovesSurrounded) {
  Board board;
  std::vector<Position> sorround = {
          Position(5, 4), Position(5, 5),
          Position(4, 5), Position(3, 5),
          Position(3, 4), Position(3, 3),
          Position(4, 3), Position(5, 3)
  };
  std::list<Position> posible_moves_gt = {
          Position(6, 5), Position(5, 6),
          Position(3, 6), Position(2, 5),
          Position(2, 3), Position(3, 2),
          Position(5, 2), Position(6, 3),
  };

  for (size_t i = 0; i < sorround.size(); i++) {
    board.addNewChessman('T', sorround[i], true);
  }

  board.addNewChessman('H', Position(4, 4), true);

  Chessman *chessman = board.getChessmanAt(Position(4, 4));

  std::list<Position> posible_moves;
  chessman->calculatePossibleMoves(Position(4, 4), posible_moves);

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Pawn, PosibleMoveWithEmptyBoard) {
  Board board;
  board.addNewChessman('P', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  std::list<Position> posible_moves_gt = {
          Position(1, 2), Position(1, 3),
  };

  std::list<Position> posible_moves;
  chessman->calculatePossibleMoves(Position(1, 1), posible_moves);

  EXPECT_EQ(posible_moves, posible_moves_gt);

  chessman->move(Position(1, 1), Position(1, 3));

  posible_moves_gt = {
          Position(1, 4)
  };

  chessman->calculatePossibleMoves(Position(1, 3), posible_moves);

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Pawn, PosibleMoveWithChessmanInPositionToCaptureButSameColor) {
  Board board;
  board.addNewChessman('P', Position(1, 1), true);

  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  board.addNewChessman('P', Position(2, 2), true);
  board.addNewChessman('P', Position(0, 2), true);

  std::list<Position> posible_moves_gt = {
          Position(1, 2), Position(1, 3)
  };

  std::list<Position> posible_moves;
  chessman->calculatePossibleMoves(Position(1, 1), posible_moves);

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Pawn, PosibleMoveWithChessmanInPositionToCapture) {
  Board board;
  board.addNewChessman('P', Position(1, 1), true);

  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  board.addNewChessman('P', Position(2, 2), false);
  board.addNewChessman('P', Position(0, 2), false);

  std::list<Position> posible_moves_gt = {
          Position(1, 2), Position(2, 2),
          Position(0, 2), Position(1, 3)
  };

  std::list<Position> posible_moves;
  chessman->calculatePossibleMoves(Position(1, 1), posible_moves);

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(Chessman, OneSplit) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 2, 0.5));
  EXPECT_EQ(QuantumPosition(2, 2, 0.5), chessman->getPosition(1));
}

TEST(Chessman, TwoSplitsSplittingReal) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
  chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 3, 0.25));
  EXPECT_EQ(QuantumPosition(2, 1, 0.25), chessman->getPosition(1));
  EXPECT_EQ(QuantumPosition(2, 2, 0.5), chessman->getPosition(2));
}

TEST(Chessman, TwoSplitsSplittingFake) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
  chessman->split(Position(2, 2), Position(2, 3), Position(2, 1));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 2, 0.5));
  EXPECT_EQ(QuantumPosition(2, 3, 0.25), chessman->getPosition(1));
  EXPECT_EQ(QuantumPosition(2, 1, 0.25), chessman->getPosition(2));
}

TEST(Chessman, SplitThenMoveSplitted) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2),
                  Position(2, 2));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 2, 0.5));
  EXPECT_EQ(QuantumPosition(2, 2, 0.5), chessman->getPosition(1));

  chessman->move(Position(1, 2), Position(1, 3));
  chessman->move(Position(2, 2), Position(2, 3));
  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 3, 0.5));
  EXPECT_EQ(QuantumPosition(2, 3, 0.5), chessman->getPosition(1));
}

TEST(Chessman, OneBadSplitToSamePosition) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  EXPECT_THROW(chessman->split(Position(1, 1), Position(1, 1),
                               Position(2, 2)), ChessException);
}

TEST(Chessman, OneBadSplitToInvalidPosition) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  EXPECT_THROW(chessman->split(Position(1, 1), Position(1, 1),
                               Position(3, 2)), ChessException);
}

TEST(Chessman, SplitToSamePosition) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  EXPECT_THROW(chessman->split(Position(1, 1), Position(2, 2),
                               Position(2, 2)), ChessException);
}

TEST(Chessman, MergeOneSplit) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));

  chessman->merge(Position(1, 2), Position(2, 2), Position(1, 3));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 3, 1));
}

TEST(Chessman, MergeTwoSplitsSplittingRealMergingTheTwoFakes) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
  chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

  chessman->merge(Position(2, 2), Position(2, 1), Position(1, 1));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 3, 0.25));
  EXPECT_EQ(chessman->getPosition(1), QuantumPosition(1, 1, 0.75));
}

TEST(Chessman, MergeTwoSplitsSplittingRealMergingRealWithFake) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
  chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

  chessman->merge(Position(1, 3), Position(2, 2), Position(1, 1));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 1, 0.75));
  EXPECT_EQ(chessman->getPosition(1), QuantumPosition(2, 1, 0.25));
}

TEST(Chessman, TwoSplitsSplittingFakeMergingFakes) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
  chessman->split(Position(2, 2), Position(2, 3), Position(2, 1));

  chessman->merge(Position(2, 3), Position(2, 1), Position(2, 2));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 2, 0.5));
  EXPECT_EQ(chessman->getPosition(1), QuantumPosition(2, 2, 0.5));
}

TEST(Chessman, SplitThenMoveSplittedThenMerge) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2),
                  Position(2, 2));

  chessman->move(Position(1, 2), Position(1, 3));
  chessman->move(Position(2, 2), Position(2, 3));

  chessman->merge(Position(1, 3), Position(2, 3), Position(2, 4));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(2, 4, 1));
}

TEST(Chessman, MergeOneSplitToPositionOfOneOfThem) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));

  chessman->merge(Position(1, 2), Position(2, 2), Position(2, 2));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(2, 2, 1));
}

TEST(Chessman, MergeOneSplitToPositionInTheSameLine) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(1, 3));

  EXPECT_THROW(chessman->merge(Position(1, 2), Position(1, 3), Position(1, 1)),
               ChessException);
}

TEST(Chessman, OneBadMergeToInvalidPosition) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2),
                  Position(2, 2));

  EXPECT_THROW(chessman->merge(Position(1, 2), Position(2, 2),
                               Position(3, 3)), ChessException);
}

TEST(Chessman, MergeFromSamePosition) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2),
                  Position(2, 2));

  EXPECT_THROW(chessman->merge(Position(1, 2), Position(1, 2),
                               Position(3, 3)), ChessException);
}


TEST(Chessman, OneSplitMeasureReal) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));

  chessman->measure(Position(1, 2));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(chessman->positionsAmount(), 1);
}

TEST(Chessman, OneSplitMeasureFake) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));

  chessman->measure(Position(2, 2));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(chessman->positionsAmount(), 1);
}

TEST(Chessman, TwoSplitsSplittingRealMeasureReal) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
  chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

  chessman->measure(Position(1, 3));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 3, 1));
  EXPECT_EQ(chessman->positionsAmount(), 1);
}

TEST(Chessman, TwoSplitsSplittingRealMeasureFakeFirstSplit) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
  chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

  chessman->measure(Position(2, 2));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 3, 0.5));
  EXPECT_EQ(chessman->getPosition(1), QuantumPosition(2, 1, 0.5));
  EXPECT_EQ(chessman->positionsAmount(), 2);
}

TEST(Chessman, TwoSplitsSplittingRealMeasureFakeSecondSplit) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
  chessman->split(Position(1, 2), Position(1, 3), Position(2, 1));

  chessman->measure(Position(2, 1));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 3, 0.25 / 0.75));
  EXPECT_EQ(chessman->getPosition(1),
            QuantumPosition(2, 2, 0.5 / 0.75));
  EXPECT_EQ(chessman->positionsAmount(), 2);
}

TEST(Chessman, TwoSplitsSplittingFakeMeasuringOneOfThem) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
  chessman->split(Position(2, 2), Position(2, 3), Position(2, 1));

  chessman->measure(Position(2, 3));

  EXPECT_EQ(chessman->getPosition(), QuantumPosition(1, 2, 0.5 / 0.75));
  EXPECT_EQ(QuantumPosition(2, 1, 0.25 / 0.75),
            chessman->getPosition(1));
  EXPECT_EQ(chessman->positionsAmount(), 2);
}

TEST(Chessman, MeasureOtherPosition) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  Chessman *chessman = board.getChessmanAt(Position(1, 1));

  chessman->split(Position(1, 1), Position(1, 2), Position(2, 2));
  chessman->split(Position(2, 2), Position(2, 3), Position(2, 1));

  EXPECT_THROW(chessman->measure(Position(4, 4)), ChessException);
}

TEST(Chessman, MoveWithTwoQuantumInTheMiddle) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(2, 2), Position(4, 4));
  queen->split(Position(2, 2), Position(3, 3), Position(2, 3));
  EXPECT_THROW(bishop->move(Position(0, 0), Position(5, 5)), ChessException);
}

TEST(Chessman, MoveClassicWithMeasureToFakeQuantumPieceOfSameColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
  bishop->move(Position(0, 0), Position(3, 3));
  EXPECT_EQ(bishop->getPosition(), QuantumPosition(3, 3, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, MoveClassicWithMeasureToRealQuantumPieceOfSameColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
  bishop->move(Position(0, 0), Position(3, 3));
  EXPECT_EQ(bishop->getPosition(), QuantumPosition(0, 0, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(3, 3, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, MoveClassicWithMeasureToRealQuantumPieceOfDifferentColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), false);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
  bishop->move(Position(0, 0), Position(3, 3));
  EXPECT_EQ(bishop->getPosition(), QuantumPosition(3, 3, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_FALSE(board.isThere(queen));
}

TEST(Chessman, MoveClassicWithMeasureToFakeQuantumPieceOfDifferentColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
  bishop->move(Position(0, 0), Position(3, 3));
  EXPECT_EQ(bishop->getPosition(), QuantumPosition(3, 3, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}


// TODO que pasa si son del mismo palo.
TEST(Chessman, MoveRealQPieceWithMeasureToClassicAndCaptureDifferentColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), false);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
  queen->move(Position(3, 3), Position(0, 0));
  EXPECT_EQ(queen->getPosition(), QuantumPosition(0, 0, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
  EXPECT_FALSE(board.isThere(bishop));
}

TEST(Chessman, MoveClassicWithMeasureToFakeQuantumPieceDifferentColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), false);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
  queen->move(Position(3, 3), Position(0, 0));
  EXPECT_EQ(bishop->getPosition(), QuantumPosition(0, 0, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
  EXPECT_TRUE(board.isThere(bishop));
}

TEST(Chessman, MoveRealQuantumPieceWithMeasureToClassicAndCaptureSameColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));

  queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
  EXPECT_THROW(queen->move(Position(3, 3), Position(0, 0)), ChessException);
}

TEST(Chessman, MoveFakeQuantumPieceWithMeasureToClassicAndCaptureSameColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));

  queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
  EXPECT_THROW(queen->move(Position(3, 3), Position(0, 0)), ChessException);
}

TEST(Chessman, MoveMeasureFromRealQuantumToRealQuantumOfDifferentColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('Q', Position(0, 0), false);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *queen_2 = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
  queen_2->split(Position(0, 0), Position(1, 1), Position(0, 1));
  queen_2->move(Position(1, 1), Position(3, 3));
  EXPECT_EQ(queen_2->getPosition(), QuantumPosition(3, 3, 1));
  EXPECT_EQ(queen_2->positionsAmount(), 1);
  EXPECT_FALSE(board.isThere(queen));
}

TEST(Chessman, MoveMeasureFromRealQuantumToFakeQuantumOfDifferentColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('Q', Position(0, 0), false);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *queen_2 = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
  queen_2->split(Position(0, 0), Position(1, 1), Position(0, 1));
  queen_2->move(Position(1, 1), Position(3, 3));
  EXPECT_EQ(queen_2->getPosition(), QuantumPosition(3, 3, 1));
  EXPECT_EQ(queen_2->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, MoveMeasureFromFakeQuantumToRealQuantumOfDifferentColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('Q', Position(0, 0), false);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *queen_2 = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(3, 3), Position(1, 2));
  queen_2->split(Position(0, 0), Position(0, 1), Position(1, 1));
  queen_2->move(Position(1, 1), Position(3, 3));
  EXPECT_EQ(queen_2->getPosition(), QuantumPosition(0, 1, 1));
  EXPECT_EQ(queen_2->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(3, 3, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, MoveMeasureFromFakeQuantumToFakeQuantumOfDifferentColor) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('Q', Position(0, 0), false);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *queen_2 = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
  queen_2->split(Position(0, 0), Position(0, 1), Position(1, 1));
  queen_2->move(Position(1, 1), Position(3, 3));
  EXPECT_EQ(queen_2->getPosition(), QuantumPosition(0, 1, 1));
  EXPECT_EQ(queen_2->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, CantSplitAndEntangle) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('Q', Position(0, 0), false);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *queen_2 = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
  EXPECT_THROW(queen_2->split(Position(0, 0), Position(0, 1), Position(3, 3)),
               ChessException);
}

TEST(Chessman, CantMergeAndEntangle) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('Q', Position(0, 0), false);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *queen_2 = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(3, 3));
  queen_2->split(Position(0, 0), Position(0, 1), Position(2, 2));
  EXPECT_THROW(queen->merge(Position(3, 3), Position(1, 2), Position(1, 1)),
               ChessException);
}

TEST(Chessman, MoveWithOneQuantumFakeInTheMiddle) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
  bishop->move(Position(0, 0), Position(4, 4));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(4, 4, 0.5));
  EXPECT_EQ(bishop->getPosition(1), QuantumPosition(0, 0, 0.5));
}

// medir entre ellos.
TEST(Chessman, EntangleWithRealThenMeasureTheOneInTheMiddleThatWasEntangled) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(2, 2), Position(1, 2));
  bishop->move(Position(0, 0), Position(4, 4));

  queen->measure(Position(2, 2));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(0, 0, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(2, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman,
     EntangleWithRealThenMeasureTheOneInTheMiddleThatWasNotEntangled) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(2, 2), Position(1, 2));
  bishop->move(Position(0, 0), Position(4, 4));

  queen->measure(Position(1, 2));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(0, 0, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(2, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, EntangleWithFakeThenMeasureTheOneInTheMiddleThatWasEntangled) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
  bishop->move(Position(0, 0), Position(4, 4));

  queen->measure(Position(2, 2));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(4, 4, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, EntangleThenMoveBothPiecesThenMeasure) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
  bishop->move(Position(0, 0), Position(4, 4));

  bishop->move(Position(4, 4), Position(5, 5));
  queen->move(Position(1, 2), Position(1, 1));

  queen->measure(Position(1, 1));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(5, 5, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 1, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}


TEST(Chessman,
     EntangleWithFakeThenMeasureTheOneInTheMiddleThatWasNotEntangled) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
  bishop->move(Position(0, 0), Position(4, 4));

  queen->measure(Position(1, 2));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(4, 4, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, EntangleWithRealThenSplitTheNonEntangledAndMeasureBothOfThem) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(2, 2), Position(1, 2));
  bishop->move(Position(0, 0), Position(4, 4));

  queen->split(Position(1, 2), Position(0, 2), Position(1, 3));

  queen->measure(Position(1, 3));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(0, 0, 0.5));
  EXPECT_EQ(bishop->getPosition(1), QuantumPosition(4, 4, 0.5));
  EXPECT_EQ(bishop->positionsAmount(), 2);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(2, 2, 0.5 / 0.75));
  EXPECT_EQ(queen->getPosition(1), QuantumPosition(0, 2, 0.25 / 0.75));
  EXPECT_EQ(queen->positionsAmount(), 2);

  queen->measure(Position(0, 2));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(0, 0, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(2, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, EntangleWithFakeThenSplitEntangledThenMeasureNonMiddle) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
  bishop->move(Position(0, 0), Position(4, 4));

  queen->split(Position(2, 2), Position(3, 3), Position(2, 3));

  bishop->measure(Position(0, 0));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(4, 4, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, EntangleWithRealThenSplitGeneratedThenMeasureOriginal) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
  bishop->move(Position(0, 0), Position(4, 4));

  bishop->split(Position(4, 4), Position(3, 3), Position(5, 5));

  bishop->measure(Position(0, 0));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(3, 3, 0.25 / 0.5));
  EXPECT_EQ(bishop->getPosition(1), QuantumPosition(5, 5, 0.25 / 0.5));
  EXPECT_EQ(bishop->positionsAmount(), 2);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}


TEST(Chessman, EntangleWithFakethenSplitNotEntangledAndMeasureEntangled) {
  Board board(false);
  board.addNewChessman('Q', Position(1, 1), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(1, 1));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(1, 1), Position(1, 2), Position(2, 2));
  bishop->move(Position(0, 0), Position(4, 4));

  queen->split(Position(1, 2), Position(0, 2), Position(1, 3));

  queen->measure(Position(2, 2));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(4, 4, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(0, 2, 0.5));
  EXPECT_EQ(queen->getPosition(1), QuantumPosition(1, 3, 0.5));
  EXPECT_EQ(queen->positionsAmount(), 2);
}

TEST(Chessman, DoubleEntangleWithRealThenMeasureMiddle) {
  Board board(false);
  board.addNewChessman('Q', Position(4, 3), true);
  board.addNewChessman('B', Position(0, 0), true);
  board.addNewChessman('B', Position(2, 6), true);
  Chessman *queen = board.getChessmanAt(Position(4, 3));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));
  Chessman *bishop_2 = board.getChessmanAt(Position(2, 6));

  queen->split(Position(4, 3), Position(4, 4), Position(4, 2));
  bishop->move(Position(0, 0), Position(7, 7));
  bishop_2->move(Position(2, 6), Position(5, 3));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(0, 0, 0.5));
  EXPECT_EQ(bishop->getPosition(1), QuantumPosition(7, 7, 0.5));
  EXPECT_EQ(bishop_2->getPosition(), QuantumPosition(2, 6, 0.5));
  EXPECT_EQ(bishop_2->getPosition(1), QuantumPosition(5, 3, 0.5));

  queen->measure(Position(4, 4));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(0, 0, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(bishop_2->getPosition(), QuantumPosition(2, 6, 1));
  EXPECT_EQ(bishop_2->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(4, 4, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, DoubleEntangleWithFakeThenMeasureMiddle) {
  Board board(false);
  board.addNewChessman('Q', Position(4, 3), true);
  board.addNewChessman('B', Position(0, 0), true);
  board.addNewChessman('B', Position(2, 6), true);
  Chessman *queen = board.getChessmanAt(Position(4, 3));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));
  Chessman *bishop_2 = board.getChessmanAt(Position(2, 6));

  queen->split(Position(4, 3), Position(4, 2), Position(4, 4));
  bishop->move(Position(0, 0), Position(7, 7));
  bishop_2->move(Position(2, 6), Position(5, 3));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(7, 7, 0.5));
  EXPECT_EQ(bishop->getPosition(1), QuantumPosition(0, 0, 0.5));
  EXPECT_EQ(bishop_2->getPosition(), QuantumPosition(5, 3, 0.5));
  EXPECT_EQ(bishop_2->getPosition(1), QuantumPosition(2, 6, 0.5));

  queen->measure(Position(4, 4));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(7, 7, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(bishop_2->getPosition(), QuantumPosition(5, 3, 1));
  EXPECT_EQ(bishop_2->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(4, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, DoubleEntangleWithRealThenMeasureOneOfOthers) {
  Board board(false);
  board.addNewChessman('Q', Position(4, 3), true);
  board.addNewChessman('B', Position(0, 0), true);
  board.addNewChessman('B', Position(2, 6), true);
  Chessman *queen = board.getChessmanAt(Position(4, 3));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));
  Chessman *bishop_2 = board.getChessmanAt(Position(2, 6));

  queen->split(Position(4, 3), Position(4, 4), Position(4, 2));
  bishop->move(Position(0, 0), Position(7, 7));
  bishop_2->move(Position(2, 6), Position(5, 3));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(0, 0, 0.5));
  EXPECT_EQ(bishop->getPosition(1), QuantumPosition(7, 7, 0.5));
  EXPECT_EQ(bishop_2->getPosition(), QuantumPosition(2, 6, 0.5));
  EXPECT_EQ(bishop_2->getPosition(1), QuantumPosition(5, 3, 0.5));

  bishop_2->measure(Position(2, 6));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(0, 0, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(bishop_2->getPosition(), QuantumPosition(2, 6, 1));
  EXPECT_EQ(bishop_2->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(4, 4, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, DoubleEntangleWithFakeThenMeasureOneOfOthers) {
  Board board(false);
  board.addNewChessman('Q', Position(4, 3), true);
  board.addNewChessman('B', Position(0, 0), true);
  board.addNewChessman('B', Position(2, 6), true);
  Chessman *queen = board.getChessmanAt(Position(4, 3));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));
  Chessman *bishop_2 = board.getChessmanAt(Position(2, 6));

  queen->split(Position(4, 3), Position(4, 2), Position(4, 4));
  bishop->move(Position(0, 0), Position(7, 7));
  bishop_2->move(Position(2, 6), Position(5, 3));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(7, 7, 0.5));
  EXPECT_EQ(bishop->getPosition(1), QuantumPosition(0, 0, 0.5));
  EXPECT_EQ(bishop_2->getPosition(), QuantumPosition(5, 3, 0.5));
  EXPECT_EQ(bishop_2->getPosition(1), QuantumPosition(2, 6, 0.5));

  bishop->measure(Position(0, 0));

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(7, 7, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
  EXPECT_EQ(bishop_2->getPosition(), QuantumPosition(5, 3, 1));
  EXPECT_EQ(bishop_2->positionsAmount(), 1);
  EXPECT_EQ(queen->getPosition(), QuantumPosition(4, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, DoubleEntangleSamePieceFail) {
  Board board(false);
  board.addNewChessman('Q', Position(4, 3), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(4, 3));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(4, 3), Position(4, 2), Position(4, 4));
  bishop->move(Position(0, 0), Position(7, 7));

  EXPECT_THROW(bishop->move(Position(7, 7), Position(3, 3)), ChessException);
}

TEST(Chessman, SplitUntilReachLimit) {
  Board board(false);
  board.addNewChessman('Q', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(0, 0));

  queen->split(Position(0, 0), Position(0, 1), Position(0, 2));
  queen->split(Position(0, 2), Position(0, 3), Position(0, 4));
  queen->split(Position(0, 4), Position(0, 5), Position(0, 6));
  queen->split(Position(0, 6), Position(0, 7), Position(1, 7));
  queen->split(Position(1, 7), Position(1, 6), Position(1, 5));
  queen->split(Position(1, 5), Position(1, 4), Position(1, 3));
  queen->split(Position(1, 3), Position(1, 2), Position(1, 1));
  queen->split(Position(1, 1), Position(1, 0), Position(2, 0));
  queen->split(Position(2, 0), Position(2, 1), Position(2, 2));
  queen->split(Position(2, 2), Position(2, 3), Position(2, 4));
  queen->split(Position(2, 4), Position(2, 5), Position(2, 6));
  queen->split(Position(2, 6), Position(2, 7), Position(3, 7));
  queen->split(Position(3, 7), Position(3, 6), Position(3, 5));
  queen->split(Position(3, 5), Position(3, 4), Position(3, 3));
  queen->split(Position(3, 3), Position(3, 2), Position(3, 1));
  queen->split(Position(3, 1), Position(3, 0), Position(4, 0));

  EXPECT_THROW(queen->split(Position(4, 0), Position(4, 1), Position(4, 2)),
               ChessException);

  queen->measure(Position(0, 1));

  EXPECT_EQ(queen->getPosition(), QuantumPosition(0, 1, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
}

TEST(Chessman, EntangleThenSplitThenMergeThenMeasure) {
  Board board(false);
  board.addNewChessman('Q', Position(4, 3), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(4, 3));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(4, 3), Position(4, 2), Position(4, 4));
  bishop->move(Position(0, 0), Position(7, 7));

  bishop->split(Position(7, 7), Position(6, 6), Position(5, 5));
  bishop->merge(Position(6, 6), Position(5, 5), Position(6, 6));

  bishop->measure(Position(6, 6));

  EXPECT_EQ(queen->getPosition(), QuantumPosition(4, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(6, 6, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
}

TEST(Chessman, EntangleThenSplitTHenMergeThenMeasure) {
  Board board(false);
  board.addNewChessman('Q', Position(4, 3), true);
  board.addNewChessman('B', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(4, 3));
  Chessman *bishop = board.getChessmanAt(Position(0, 0));

  queen->split(Position(4, 3), Position(4, 2), Position(4, 4));
  bishop->move(Position(0, 0), Position(7, 7));

  bishop->split(Position(7, 7), Position(6, 6), Position(5, 5));
  bishop->merge(Position(6, 6), Position(5, 5), Position(6, 6));

  bishop->measure(Position(6, 6));

  EXPECT_EQ(queen->getPosition(), QuantumPosition(4, 2, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);

  EXPECT_EQ(bishop->getPosition(), QuantumPosition(6, 6, 1));
  EXPECT_EQ(bishop->positionsAmount(), 1);
}


TEST(Chessman,
     EntangleThenMergeOneEntangledOtherNonEntangledThenMeasEntangled) {
  Board board(false);
  board.addNewChessman('Q', Position(0, 0), true);
  board.addNewChessman('Q', Position(4, 3), true);
  Chessman *queen_2 = board.getChessmanAt(Position(4, 3));
  Chessman *queen = board.getChessmanAt(Position(0, 0));

  queen_2->split(Position(4, 3), Position(4, 2), Position(4, 4));
  queen->move(Position(0, 0), Position(7, 7));
  queen_2->move(Position(4, 4), Position(4, 5));


  queen->merge(Position(0, 0), Position(7, 7), Position(5, 5));


  EXPECT_EQ(queen->getPosition(), QuantumPosition(5, 5, 1));

  queen->measure(Position(5, 5));

  EXPECT_EQ(queen->getPosition(), QuantumPosition(5, 5, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
  EXPECT_EQ(queen_2->getPosition(), QuantumPosition(4, 2, 0.5));
  EXPECT_EQ(queen_2->getPosition(1), QuantumPosition(4, 5, 0.5));
  EXPECT_EQ(queen_2->positionsAmount(), 2);
}

TEST(Chessman,
     EntangleThenSplitThenMergeOneEntangledOtherNonEntangledThenMeasEntangled) {
  Board board(false);
  board.addNewChessman('Q', Position(0, 0), true);
  board.addNewChessman('Q', Position(4, 3), true);
  Chessman *queen_2 = board.getChessmanAt(Position(4, 3));
  Chessman *queen = board.getChessmanAt(Position(0, 0));

  queen_2->split(Position(4, 3), Position(4, 2), Position(4, 4));
  queen->move(Position(0, 0), Position(7, 7));
  queen_2->move(Position(4, 4), Position(4, 5));


  queen->split(Position(7, 7), Position(6, 6), Position(5, 5));
  queen->merge(Position(0, 0), Position(5, 5), Position(5, 5));


  EXPECT_EQ(queen->getPosition(), QuantumPosition(6, 6, 0.25));
  EXPECT_EQ(queen->getPosition(1), QuantumPosition(5, 5, 0.75));

  queen->measure(Position(5, 5));

  EXPECT_EQ(queen->getPosition(), QuantumPosition(6, 6, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
  EXPECT_EQ(queen_2->getPosition(), QuantumPosition(4, 2, 1));
  EXPECT_EQ(queen_2->positionsAmount(), 1);
}

TEST(Chessman, EntangleWithItselfFails) {
  Board board(false);
  board.addNewChessman('Q', Position(0, 0), true);
  Chessman *queen = board.getChessmanAt(Position(0, 0));

  queen->split(Position(0, 0), Position(1, 1), Position(4, 4));

  EXPECT_THROW(queen->move(Position(1, 1), Position(5, 5)), ChessException);
}

TEST(Pawn, PawnCannotSplitMergeNorEntangle) {
  Board board(false);
  board.addNewChessman('P', Position(5, 0), true);
  board.addNewChessman('Q', Position(4, 0), true);
  Chessman *pawn = board.getChessmanAt(Position(5, 0));
  Chessman *queen = board.getChessmanAt(Position(4, 0));

  EXPECT_THROW(pawn->split(Position(5, 0), Position(5, 1), Position(5, 2)),
               ChessException);
  EXPECT_THROW(pawn->merge(Position(5, 0), Position(5, 1), Position(5, 2)),
               ChessException);

  queen->split(Position(4, 0), Position(4, 1), Position(5, 1));

  EXPECT_THROW(pawn->move(Position(5, 0), Position(5, 2)), ChessException);
}

TEST(Chessman, calculatePosibleSplitsWithEmptyBoardAndEnemy) {
  Board board(false);
  board.addNewChessman('T', Position(5, 1), true);
  Chessman *tower = board.getChessmanAt(Position(5, 1));

  std::list<Position> posible_splits;

  tower->calculatePossibleSplits(Position(5, 1), posible_splits);

  std::list<Position> posible_splits_gt = {
          Position(5, 0), Position(5, 2),
          Position(5, 3), Position(5, 4),
          Position(5, 5), Position(5, 6),
          Position(5, 7), Position(0, 1),
          Position(1, 1), Position(2, 1),
          Position(3, 1), Position(4, 1),
          Position(6, 1), Position(7, 1),
  };

  EXPECT_EQ(posible_splits, posible_splits_gt);

  board.addNewChessman('Q', Position(5, 7), false);
  tower->calculatePossibleSplits(Position(5, 1), posible_splits);

  posible_splits_gt = {
          Position(5, 0), Position(5, 2), Position(5, 3), Position(5, 4),
          Position(5, 5), Position(5, 6), Position(0, 1), Position(1, 1),
          Position(2, 1), Position(3, 1), Position(4, 1), Position(6, 1),
          Position(7, 1),
  };

  EXPECT_EQ(posible_splits, posible_splits_gt);
}

TEST(Chessman, calculatePosibleMergeWithEmptyBoardAndEnemy) {
  Board board;
  board.addNewChessman('T', Position(4, 1), true);
  Chessman *tower = board.getChessmanAt(Position(4, 1));
  std::list<Position> posible_merges;

  tower->split(Position(4, 1), Position(5, 1), Position(4, 2));

  tower->calculatePossibleMerges(Position(5, 1), posible_merges);

  std::list<Position> posible_merges_gt = {
          Position(5, 0), Position(5, 2),
          Position(5, 3), Position(5, 4),
          Position(5, 5), Position(5, 6),
          Position(5, 7), Position(0, 1),
          Position(1, 1), Position(2, 1),
          Position(3, 1), Position(4, 1), Position(6, 1),
          Position(7, 1), Position(5, 1)
  };

  EXPECT_EQ(posible_merges, posible_merges_gt);

  board.addNewChessman('Q', Position(5, 7), false);
  tower->calculatePossibleMerges(Position(5, 1), posible_merges);

  posible_merges_gt = {
          Position(5, 0), Position(5, 2), Position(5, 3), Position(5, 4),
          Position(5, 5), Position(5, 6), Position(0, 1), Position(1, 1),
          Position(2, 1), Position(3, 1), Position(4, 1),
          Position(6, 1), Position(7, 1), Position(5, 1)
  };

  EXPECT_EQ(posible_merges, posible_merges_gt);
}

TEST(Chessman, calculatePosibleMergeWithEmptyBoardAndAlly) {
  Board board;
  board.addNewChessman('T', Position(4, 1), true);
  Chessman *tower = board.getChessmanAt(Position(4, 1));
  std::list<Position> posible_merges;

  tower->split(Position(4, 1), Position(5, 1), Position(4, 2));

  tower->calculatePossibleMerges(Position(5, 1), posible_merges);

  std::list<Position> posible_merges_gt = {
          Position(5, 0), Position(5, 2),
          Position(5, 3), Position(5, 4),
          Position(5, 5), Position(5, 6),
          Position(5, 7), Position(0, 1),
          Position(1, 1), Position(2, 1),
          Position(3, 1), Position(4, 1),
          Position(6, 1), Position(7, 1), Position(5, 1)
  };

  EXPECT_EQ(posible_merges, posible_merges_gt);

  board.addNewChessman('Q', Position(5, 7), true);
  tower->calculatePossibleMerges(Position(5, 1), posible_merges);

  posible_merges_gt = {
          Position(5, 0), Position(5, 2),
          Position(5, 3), Position(5, 4),
          Position(5, 5), Position(5, 6),
          Position(5, 7), Position(0, 1),
          Position(1, 1), Position(2, 1),
          Position(3, 1), Position(4, 1),
          Position(6, 1), Position(7, 1), Position(5, 1)
  };

  EXPECT_EQ(posible_merges, posible_merges_gt);
}

TEST(Chessman, MergeOnClassicChessmanDoesntHaveAnyPossibleMerge) {
  Board board;
  board.addNewChessman('T', Position(5, 1), true);
  Chessman *tower = board.getChessmanAt(Position(5, 1));
  std::list<Position> posible_merges;

  tower->calculatePossibleMerges(Position(5, 1), posible_merges);

  std::list<Position> posible_merges_gt = {};

  EXPECT_EQ(posible_merges, posible_merges_gt);
}

TEST(Chessman, CannotMergeDifferentChessman) {
  Board board;
  board.addNewChessman('T', Position(4, 1), true);
  board.addNewChessman('T', Position(7, 1), true);
  Chessman *tower_1 = board.getChessmanAt(Position(4, 1));
  Chessman *tower_2 = board.getChessmanAt(Position(7, 1));
  std::list<Position> posible_merges;

  tower_1->split(Position(4, 1), Position(5, 1), Position(4, 2));
  tower_2->split(Position(7, 1), Position(7, 2), Position(6, 1));

  EXPECT_THROW(tower_2->merge(Position(6, 1), Position(5, 1), Position(6, 1)),
               ChessException);
}

TEST(King, CastlingKingHasMovementAvailableWithTowerToLeft) {
  Board board;
  board.addNewChessman('T', Position(0, 0), true);
  board.addNewChessman('K', Position(4, 0), true);
  Chessman *tower = board.getChessmanAt(Position(0, 0));
  Chessman *king = board.getChessmanAt(Position(4, 0));

  std::list<Position> posible_moves;

  king->calculatePossibleMoves(Position(4, 0), posible_moves);

  std::list<Position> posible_moves_gt = {
          Position(5, 0), Position(5, 1),
          Position(4, 1), Position(3, 1),
          Position(3, 0), Position(2, 0)
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(King, CastlingKingHasMovementAvailableWithTowerToRight) {
  Board board;
  board.addNewChessman('T', Position(7, 0), true);
  board.addNewChessman('K', Position(4, 0), true);
  Chessman *tower = board.getChessmanAt(Position(0, 0));
  Chessman *king = board.getChessmanAt(Position(4, 0));

  std::list<Position> posible_moves;

  king->calculatePossibleMoves(Position(4, 0), posible_moves);

  std::list<Position> posible_moves_gt = {
          Position(5, 0), Position(5, 1),
          Position(4, 1), Position(3, 1),
          Position(3, 0), Position(6, 0)
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(King, AlreadyMovedTowerCantCastle) {
  Board board;
  board.addNewChessman('T', Position(0, 0), true);
  board.addNewChessman('K', Position(4, 0), true);
  Chessman *tower = board.getChessmanAt(Position(0, 0));
  Chessman *king = board.getChessmanAt(Position(4, 0));

  std::list<Position> posible_moves;

  tower->move(Position(0, 0), Position(1, 0));
  tower->move(Position(1, 0), Position(0, 0));

  king->calculatePossibleMoves(Position(4, 0), posible_moves);

  std::list<Position> posible_moves_gt = {
          Position(5, 0), Position(5, 1),
          Position(4, 1), Position(3, 1),
          Position(3, 0)
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(King, AlreadyMovedKingCantCastle) {
  Board board;
  board.addNewChessman('T', Position(0, 0), true);
  board.addNewChessman('K', Position(4, 0), true);
  Chessman *tower = board.getChessmanAt(Position(0, 0));
  Chessman *king = board.getChessmanAt(Position(4, 0));

  std::list<Position> posible_moves;

  king->move(Position(4, 0), Position(5, 0));
  king->move(Position(5, 0), Position(4, 0));

  king->calculatePossibleMoves(Position(4, 0), posible_moves);

  std::list<Position> posible_moves_gt = {
          Position(5, 0), Position(5, 1),
          Position(4, 1), Position(3, 1),
          Position(3, 0)
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(King, CantLongCastleWithClassicPieceInTheMiddleInLongCastling) {
  Board board;
  board.addNewChessman('T', Position(0, 0), true);
  board.addNewChessman('K', Position(4, 0), true);
  board.addNewChessman('Q', Position(3, 0), true);
  Chessman *tower = board.getChessmanAt(Position(0, 0));
  Chessman *king = board.getChessmanAt(Position(4, 0));
  Chessman *queen = board.getChessmanAt(Position(3, 0));

  std::list<Position> posible_moves;

  king->calculatePossibleMoves(Position(4, 0), posible_moves);

  std::list<Position> posible_moves_gt = {
          Position(5, 0), Position(5, 1),
          Position(4, 1), Position(3, 1),
  };

  queen->move(Position(3, 0), Position(2, 0));
  king->calculatePossibleMoves(Position(4, 0), posible_moves);

  posible_moves_gt = {
          Position(5, 0), Position(5, 1),
          Position(4, 1), Position(3, 1), Position(3, 0)
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);

  queen->move(Position(2, 0), Position(1, 0));
  king->calculatePossibleMoves(Position(4, 0), posible_moves);

  posible_moves_gt = {
          Position(5, 0), Position(5, 1),
          Position(4, 1), Position(3, 1), Position(3, 0)
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(King, LongCastleWithQuantumPieceInTheMiddle) {
  Board board;
  board.addNewChessman('T', Position(0, 0), true);
  board.addNewChessman('K', Position(4, 0), true);
  board.addNewChessman('Q', Position(3, 1), true);
  Chessman *tower = board.getChessmanAt(Position(0, 0));
  Chessman *king = board.getChessmanAt(Position(4, 0));
  Chessman *queen = board.getChessmanAt(Position(3, 1));

  queen->split(Position(3, 1), Position(3, 2), Position(3, 0));

  std::list<Position> posible_moves;

  king->calculatePossibleMoves(Position(4, 0), posible_moves);

  std::list<Position> posible_moves_gt = {
          Position(5, 0), Position(5, 1),
          Position(4, 1), Position(3, 1),
  };

  queen->move(Position(3, 0), Position(2, 0));
  king->calculatePossibleMoves(Position(4, 0), posible_moves);

  posible_moves_gt = {
          Position(5, 0), Position(5, 1),
          Position(4, 1), Position(3, 1), Position(3, 0)
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);

  queen->move(Position(2, 0), Position(1, 0));
  king->calculatePossibleMoves(Position(4, 0), posible_moves);

  posible_moves_gt = {
          Position(5, 0), Position(5, 1),
          Position(4, 1), Position(3, 1), Position(3, 0),
          Position(2, 0)
  };

  EXPECT_EQ(posible_moves, posible_moves_gt);
}

TEST(King, LongCastleMoveWithQuantumInTheMiddleAndThenMeasureQueenWasThere) {
  Board board(false);
  board.addNewChessman('T', Position(0, 0), true);
  board.addNewChessman('K', Position(4, 0), true);
  board.addNewChessman('Q', Position(0, 1), true);
  Chessman *tower = board.getChessmanAt(Position(0, 0));
  Chessman *king = board.getChessmanAt(Position(4, 0));
  Chessman *queen = board.getChessmanAt(Position(0, 1));

  queen->split(Position(0, 1), Position(1, 0), Position(1, 1));

  std::list<Position> posible_moves;

  king->move(Position(4, 0), Position(2, 0));

  EXPECT_EQ(king->getPosition(), QuantumPosition(4, 0, 0.5));
  EXPECT_EQ(king->getPosition(1), QuantumPosition(2, 0, 0.5));
  EXPECT_EQ(king->positionsAmount(), 2);
  EXPECT_EQ(tower->getPosition(), QuantumPosition(0, 0, 0.5));
  EXPECT_EQ(tower->getPosition(1), QuantumPosition(3, 0, 0.5));
  EXPECT_EQ(tower->positionsAmount(), 2);

  queen->measure(Position(1, 1));

  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 0, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
  EXPECT_EQ(king->getPosition(), QuantumPosition(4, 0, 1));
  EXPECT_EQ(king->positionsAmount(), 1);
  EXPECT_EQ(tower->getPosition(), QuantumPosition(0, 0, 1));
  EXPECT_EQ(tower->positionsAmount(), 1);
}

TEST(King, LongCastleMoveWithQuantumInTheMiddleAndThenMeasureQueenWasNotThere) {
  Board board(false);
  board.addNewChessman('T', Position(0, 0), true);
  board.addNewChessman('K', Position(4, 0), true);
  board.addNewChessman('Q', Position(0, 1), true);
  Chessman *tower = board.getChessmanAt(Position(0, 0));
  Chessman *king = board.getChessmanAt(Position(4, 0));
  Chessman *queen = board.getChessmanAt(Position(0, 1));

  queen->split(Position(0, 1), Position(1, 1), Position(1, 0));

  std::list<Position> posible_moves;

  king->move(Position(4, 0), Position(2, 0));

  EXPECT_EQ(king->getPosition(), QuantumPosition(2, 0, 0.5));
  EXPECT_EQ(king->getPosition(1), QuantumPosition(4, 0, 0.5));
  EXPECT_EQ(king->positionsAmount(), 2);
  EXPECT_EQ(tower->getPosition(), QuantumPosition(3, 0, 0.5));
  EXPECT_EQ(tower->getPosition(1), QuantumPosition(0, 0, 0.5));
  EXPECT_EQ(tower->positionsAmount(), 2);

  queen->measure(Position(1, 1));

  EXPECT_EQ(queen->getPosition(), QuantumPosition(1, 1, 1));
  EXPECT_EQ(queen->positionsAmount(), 1);
  EXPECT_EQ(king->getPosition(), QuantumPosition(2, 0, 1));
  EXPECT_EQ(king->positionsAmount(), 1);
  EXPECT_EQ(tower->getPosition(), QuantumPosition(3, 0, 1));
  EXPECT_EQ(tower->positionsAmount(), 1);
}
