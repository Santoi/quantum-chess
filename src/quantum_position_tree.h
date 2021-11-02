#ifndef QUANTUM_CHESS_PROJ_QUANTUM_POSITION_TREE_H
#define QUANTUM_CHESS_PROJ_QUANTUM_POSITION_TREE_H

#include <cstdint>
#include <algorithm>
#include <vector>
#include "position.h"

// TODO pensar propagacion de probs cuando pierde.

typedef std::pair<Position &, Position &> PositionPair;

class QuantumPositionTree {
    class QuantumPosition {
            Position position;
            double probability;
            QuantumPosition * top;
            QuantumPosition * left;
            QuantumPosition * right;

            friend class QuantumPositionTree;
    public:
            explicit QuantumPosition(const Position & pos, const double & probability_);
            QuantumPosition(const Position & pos, const double & probability_, QuantumPosition * top_);
            QuantumPosition * addLeft(const Position & pos);
            QuantumPosition * addRight(const Position & pos);
            ~QuantumPosition() = default;
            Position getData() const;
    };

    QuantumPosition * root;
    uint32_t size_;

    std::vector<QuantumPosition *> leaves{};

    void deleteRecursive(QuantumPosition * node);

    void updateSizeAndLeaves(QuantumPosition * node);

    bool isThere(QuantumPosition *now_node, QuantumPosition *search);

    std::vector<QuantumPositionTree::QuantumPosition *>::iterator findLeaveWithPosition(const Position & position);

public:
    explicit QuantumPositionTree(const Position & position);

    ~QuantumPositionTree();

    void split(const Position & in_position, const Position & position_1, const Position & position_2);

    // TODO revisar
    void measure(QuantumPosition * node);

    uint32_t size() const;

    uint32_t leavesSize() const;

    std::vector<Position> getLeavesData();

    void move(const Position &initial, const Position &final);
};

#endif //QUANTUM_CHESS_PROJ_QUANTUM_POSITION_TREE_H
