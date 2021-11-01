#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/quantum_position_tree.h"

TEST(QuantumPositionTree, CreateAndAddANode) {
    QuantumPositionTree binary_tree(5);

   EXPECT_EQ(binary_tree.size(), 1);
   EXPECT_EQ(binary_tree.leavesSize(), 1);
}

TEST(QuantumPositionTree, CreateAndSplit) {
    QuantumPositionTree tree(5);
    auto pair = tree.split(tree.getRoot(), 6, 7);
    tree.split(pair.first, 8, 9);

    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.leavesSize(), 3);

    std::vector<int> result = {8, 9, 7};

    EXPECT_EQ(tree.getLeavesData(), result);
}

TEST(QuantumPositionTree, CreateSplitAndMerge) {
    QuantumPositionTree tree(5);
    auto pair = tree.split(tree.getRoot(), 6, 7);
    auto pair2 = tree.split(pair.first, 8, 9);
    tree.split(pair2.first, 10, 11);



    std::vector<int> result = {10, 11, 9, 7};

    EXPECT_EQ(tree.size(), 7);
    EXPECT_EQ(tree.leavesSize(), 4);
    EXPECT_EQ(tree.getLeavesData(), result);

    tree.measure(pair.first);

    result = {10, 11, 9};

    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.leavesSize(), 3);
    EXPECT_EQ(tree.getLeavesData(), result);

    tree.measure(pair2.second);

    result = {9};

    EXPECT_EQ(tree.size(), 1);
    EXPECT_EQ(tree.leavesSize(), 1);
    EXPECT_EQ(tree.getLeavesData(), result);
}

TEST(QuantumPositionTree, SplitANonLeaveNode){
    QuantumPositionTree tree(5);
    tree.split(tree.getRoot(), 5, 6);
    EXPECT_THROW(tree.split(tree.getRoot(), 10, 11), std::invalid_argument);
}

TEST(QuantumPositionTree, MergeANonBelongingNode){
    QuantumPositionTree tree1(6);
    QuantumPositionTree tree2(5);
    tree1.split(tree1.getRoot(), 5, 6);
    auto pair = tree2.split(tree2.getRoot(), 5, 6);
    EXPECT_THROW(tree1.measure(pair.first), std::invalid_argument);
}

TEST(QuantumPositionTree, MergeARootNode){
    QuantumPositionTree tree(6);
    tree.split(tree.getRoot(), 5, 6);
    EXPECT_THROW(tree.measure(tree.getRoot()), std::invalid_argument);
}

TEST(QuantumPositionTree, Move){
    QuantumPositionTree tree(6);
    auto pair = tree.split(tree.getRoot(), 7, 8);
    tree.move(pair.first, 9);

    std::vector<int> result = {9,8};

    EXPECT_EQ(tree.getLeavesData(), result);
}