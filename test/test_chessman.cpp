#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/chessman.h"
#include "../src/board.h"

TEST(Chessman, PawnMovementFirstMove) {
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

TEST(Chessman, PawnMovement) {
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

TEST(Chessman, MoveFromANonExistingPosition) {
    Board board;
    Pawn pawn(Position(0, 1), true, board);

    EXPECT_THROW(pawn.move(Position(0, 2),
                           Position(0, 3)), std::invalid_argument);
}
