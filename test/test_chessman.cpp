#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/chessman/chessman.h"
#include "../src/board.h"
#include "../src/chessman/tower.h"

TEST(Chessman, MoveFromANonExistingPosition) {
    Board board;
    Tower tower(Position(0, 1), true, board);

    EXPECT_THROW(tower.move(Position(0, 2),
                           Position(0, 3)), std::invalid_argument);
}

TEST(Tower, CalculatePosibleMovesWithEmptyBoard) {
    Board board;
    Tower tower(Position(5, 1), true, board);
    std::vector<Position> posible_moves;

    tower.calculatePosibleMoves(Position(5, 1), posible_moves);

    std::vector<Position> posible_moves_gt = {
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
    Tower tower(Position(5, 1), true, board);

    tower.move(Position(5, 1), Position(5, 3));
    tower.move(Position(5, 3), Position(1, 3));

    EXPECT_EQ(Position(1, 3), tower.getPosition());
}

TEST(Tower, MoveWithChessmanInTheBoard) {
    Board board;
    // Se crea pieza en (5, 1)
    Tower tower(Position(5, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(7, 3), true, board);
    board.addChessman(&tower_2);

    tower.move(Position(5, 1), Position(7, 1));

    EXPECT_EQ(Position(7, 1), tower.getPosition());

    tower.move(Position(7, 1), Position(7,2));
    EXPECT_EQ(Position(7, 2), tower.getPosition());
}

TEST(Tower, BadMoveToChessmanSameColorPosition) {
    Board board;
    // Se crea pieza en (5, 1)
    Tower tower(Position(5, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(7, 1), true, board);
    board.addChessman(&tower_2);

    EXPECT_THROW(tower.move(Position(5, 1), Position(7, 1)), std::invalid_argument);
}

TEST(Tower, MoveToChessmanDiffColorPosition) {
    Board board;
    // Se crea pieza en (5, 1)
    Tower tower(Position(5, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(7, 1), false, board);
    board.addChessman(&tower_2);

    tower.move(Position(5, 1), Position(7, 1));

    EXPECT_EQ(Position(7,1), tower.getPosition());
}

TEST(Tower, BadMoveWithChessmanInTheMiddle) {
    Board board;
    // Se crea pieza en (5, 1)
    Tower tower(Position(7, 1), true, board);
    // Se crea pieza en (8, 3) y se agrega al tablero.
    Tower tower_2(Position(7, 3), true, board);
    board.addChessman(&tower_2);

    EXPECT_THROW(tower.move(Position(7,1), Position(7,5)), std::invalid_argument);
}

TEST(Tower, BadMoveWithEmptyBoard) {
    Board board;
    Tower tower(Position(5, 1), true, board);
    std::vector<Position> posible_moves;

    EXPECT_THROW(tower.move(Position(5, 1), Position(2, 3)), std::invalid_argument);
}
/*
TEST(Pawn, PawnMovementFirstMove) {
    Board board;
    Pawn pawn(Position(0, 1), true, board);

    EXPECT_TRUE(pawn.canMove(Position(0, 1), Position(0, 2)));
    EXPECT_TRUE(pawn.canMove(Position(0, 1), Position(0, 3)));
    EXPECT_FALSE(pawn.canMove(Position(0, 1), Position(0, 0)));
    EXPECT_FALSE(pawn.canMove(Position(0, 1), Position(0, 4)));
    EXPECT_FALSE(pawn.canMove(Position(0, 1), Position(1, 1)));
    EXPECT_FALSE(pawn.canMove(Position(0, 1), Position(1, 2)));
    EXPECT_FALSE(pawn.canMove(Position(0, 1), Position(0, 1)));
}

TEST(Pawn, PawnMovement) {
    Board board;
    Pawn pawn(Position(0, 1), true, board);
    pawn.move(Position(0, 1), Position(0, 2));

    EXPECT_TRUE(pawn.canMove(Position(0, 2), Position(0, 3)));
    EXPECT_FALSE(pawn.canMove(Position(0, 2), Position(0, 1)));
    EXPECT_FALSE(pawn.canMove(Position(0, 2), Position(0, 4)));
    EXPECT_FALSE(pawn.canMove(Position(0, 2), Position(1, 1)));
    EXPECT_FALSE(pawn.canMove(Position(0, 2), Position(1, 2)));
    EXPECT_FALSE(pawn.canMove(Position(0, 2), Position(0, 2)));
}

TEST(Knight, KnightCanMove) {
    Board board;
    Knight knight(Position(4, 3), true, board);

    EXPECT_TRUE(knight.canMove(Position(4, 3), Position(2, 2)));
    EXPECT_TRUE(knight.canMove(Position(4, 3), Position(2, 4)));
    EXPECT_TRUE(knight.canMove(Position(4, 3), Position(3, 1)));
    EXPECT_TRUE(knight.canMove(Position(4, 3), Position(3, 5)));
    EXPECT_TRUE(knight.canMove(Position(4, 3), Position(5, 1)));
    EXPECT_TRUE(knight.canMove(Position(4, 3), Position(5, 5)));
    EXPECT_TRUE(knight.canMove(Position(4, 3), Position(6, 2)));
    EXPECT_TRUE(knight.canMove(Position(4, 3), Position(6, 4)));
}

TEST(Knight, KnightCantMove) {
    Board board;
    Knight knight(Position(4, 3), true, board);

    EXPECT_FALSE(knight.canMove(Position(4, 3), Position(4, 4)));
    EXPECT_FALSE(knight.canMove(Position(4, 3), Position(5, 4)));
}
*/
// TODO test pieza en el medio.
