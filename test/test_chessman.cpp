#include <gtest/gtest.h>
#include "../src/chessman.h"

TEST(Chessman, PawnMovementFirstMove) {
    Pawn pawn(Position(0, 1));

    EXPECT_TRUE(pawn.canMove(Position(0, 2)));
    EXPECT_TRUE(pawn.canMove(Position(0, 3)));
    EXPECT_FALSE(pawn.canMove(Position(0, 0)));
    EXPECT_FALSE(pawn.canMove(Position(0, 4)));
    EXPECT_FALSE(pawn.canMove(Position(1, 1)));
    EXPECT_FALSE(pawn.canMove(Position(1, 2)));
    EXPECT_FALSE(pawn.canMove(Position(0, 1)));
}

TEST(Chessman, PawnMovement) {
    Pawn pawn(Position(0, 1));
    pawn.move(Position(0, 2));

    EXPECT_TRUE(pawn.canMove(Position(0, 3)));
    EXPECT_FALSE(pawn.canMove(Position(0, 1)));
    EXPECT_FALSE(pawn.canMove(Position(0, 4)));
    EXPECT_FALSE(pawn.canMove(Position(1, 1)));
    EXPECT_FALSE(pawn.canMove(Position(1, 2)));
    EXPECT_FALSE(pawn.canMove(Position(0, 2)));
}