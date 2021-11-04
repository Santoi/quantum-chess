#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include "../src/quantum_position_tree.h"

TEST(QuantumPositionTree, CreateAndAddANode) {
    QuantumPositionTree binary_tree(Position(5, 2));

   EXPECT_EQ(binary_tree.size(), 1);
   EXPECT_EQ(binary_tree.leavesSize(), 1);
}

TEST(QuantumPositionTree, CreateAndSplit) {
    QuantumPositionTree tree(Position(0, 0));
    tree.split(Position(0, 0), Position(2, 2), Position(3, 3));
    tree.split(Position(2, 2), Position(4, 4), Position(5, 5));

    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.leavesSize(), 3);

    std::vector<Position> result = {Position(4, 4),
                                    Position(5, 5), Position(3, 3)};

    EXPECT_EQ(tree.getLeavesData(), result);
}


TEST(QuantumPositionTree, SplitANonLeaveNode){
    QuantumPositionTree tree(Position(0, 0));
    tree.split(Position(0, 0), Position(1, 1), Position(2, 2));
    EXPECT_THROW(tree.split(Position(0, 1), Position(2, 2), Position(3, 5)),
                 std::invalid_argument);
}

TEST(QuantumPositionTree, Move){
    QuantumPositionTree tree(Position(0, 0));
    tree.move(Position(0,0), Position(1, 0));

    std::vector<Position> result = {Position(1, 0)};

    EXPECT_EQ(result, tree.getLeavesData());
    EXPECT_EQ(tree.size(), 1);
    EXPECT_EQ(tree.leavesSize(), 1);
}

TEST(QuantumPositionTree, MoveFromInexistentPosition){
    QuantumPositionTree tree(Position(0, 0));

    EXPECT_THROW(tree.move(Position(1,1), Position(1, 0)),
                 std::invalid_argument);
}
