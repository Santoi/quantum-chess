#include <gtest/gtest.h>
#include "../src/position.h"

TEST(Position, Equals){
    EXPECT_TRUE(Position(5, 2) == Position(5, 2));
    EXPECT_FALSE(Position(5, 2) == Position(5, 3));
    EXPECT_FALSE(Position(3, 2) == Position(5, 2));
}

TEST(Position, NotEquals){
    EXPECT_FALSE(Position(5, 2) != Position(5, 2));
    EXPECT_TRUE(Position(5, 2) != Position(5, 3));
    EXPECT_TRUE(Position(3, 2) != Position(5, 2));
}


