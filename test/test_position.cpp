#include <gtest/gtest.h>
#include "../src/server/src/quantum_chess/position.h"
#include "../src/server/src/quantum_chess/quantum_position.h"

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

TEST(QuantumPosition, Equals){
    EXPECT_TRUE(QuantumPosition(Position(5, 5), 1) ==
                                        QuantumPosition(Position(5, 5), 1));
    EXPECT_FALSE(QuantumPosition(Position(5, 4), 1) ==
                                        QuantumPosition(Position(5, 2), 1));
    EXPECT_FALSE(QuantumPosition(Position(5, 5), 1) ==
                                        QuantumPosition(Position(5, 5), 0.5));
    EXPECT_FALSE(QuantumPosition(Position(2, 5), 1) ==
                                        QuantumPosition(Position(3, 5), 1));
    EXPECT_FALSE(QuantumPosition(Position(5, 2), 1) ==
                                        QuantumPosition(Position(5, 5), 0.75));
}

TEST(QuantumPosition, NotEquals){
    EXPECT_FALSE(QuantumPosition(Position(5, 5), 1) !=
                                        QuantumPosition(Position(5, 5), 1));
    EXPECT_TRUE(QuantumPosition(Position(5, 4), 1) !=
                                        QuantumPosition(Position(5, 2), 1));
    EXPECT_TRUE(QuantumPosition(Position(5, 5), 1) !=
                                        QuantumPosition(Position(5, 5), 0.5));
    EXPECT_TRUE(QuantumPosition(Position(2, 5), 1) !=
                                        QuantumPosition(Position(3, 5), 1));
    EXPECT_TRUE(QuantumPosition(Position(5, 2), 1) !=
                                        QuantumPosition(Position(5, 5), 0.75));
}

TEST(PositionAndQuantumPosition, Equals){
    EXPECT_TRUE(Position(5, 4) == QuantumPosition(Position(5, 4), 0.5));
    EXPECT_FALSE(Position(5, 4) == QuantumPosition(Position(5, 2), 1));
    EXPECT_FALSE(Position(4, 4) == QuantumPosition(Position(3, 5), 1));

    EXPECT_TRUE(QuantumPosition(Position(5, 4), 0.5) == Position(5, 4));
    EXPECT_FALSE(QuantumPosition(Position(5, 2), 1) == Position(5, 4));
    EXPECT_FALSE(QuantumPosition(Position(3, 5), 1) == Position(4, 4));
}



