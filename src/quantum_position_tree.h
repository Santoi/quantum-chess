#ifndef QUANTUM_CHESS_PROJ_QUANTUM_POSITION_TREE_H
#define QUANTUM_CHESS_PROJ_QUANTUM_POSITION_TREE_H

#include <cstdint>
#include <algorithm>
#include <vector>

// TODO pensar propagacion de probs cuando pierde.

class QuantumPositionTree;

class QuantumPosition {
    int data;
    double probability;
    QuantumPosition * top;
    QuantumPosition * left;
    QuantumPosition * right;

    friend class QuantumPositionTree;

    explicit QuantumPosition(const int & data, const double & probability_);
    QuantumPosition(const int & data, const double & probability_, QuantumPosition * top_);
    QuantumPosition * addLeft(const int & data);
    QuantumPosition * addRight(const int & data);
    ~QuantumPosition();
    int getData() const;
};

class QuantumPositionTree {
    QuantumPosition * root;
    uint32_t size_;

    std::vector<const QuantumPosition *> leaves{};

    void deleteRecursive(QuantumPosition * node);

    void updateSizeAndLeaves(QuantumPosition * node);

    bool isThere(QuantumPosition *now_node, QuantumPosition *search);

public:
    explicit QuantumPositionTree(const int & data);

    ~QuantumPositionTree();

    std::pair<QuantumPosition *, QuantumPosition *> split(QuantumPosition * node, const int & data_1, const int & data_2);

    // TODO revisar
    void measure(QuantumPosition * node);

    void move(QuantumPosition * node, const int & data);

    uint32_t size() const;

    uint32_t leavesSize() const;

    QuantumPosition * getRoot() const;

    std::vector<int> getLeavesData();
};

#endif //QUANTUM_CHESS_PROJ_QUANTUM_POSITION_TREE_H
