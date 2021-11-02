#include "quantum_position_tree.h"
#include <algorithm>
#include <stdexcept>

QuantumPositionTree::QuantumPosition::QuantumPosition(const Position & pos, const double & probability_): position(pos), probability(probability_), top(nullptr), left(nullptr), right(nullptr) {}

QuantumPositionTree::QuantumPosition::QuantumPosition(const Position & pos, const double & probability_, QuantumPosition * top_): position(pos), probability(probability_), top(top_), left(nullptr), right(nullptr) {}

QuantumPositionTree::QuantumPosition * QuantumPositionTree::QuantumPosition::addRight(const Position & pos) {
    right = new QuantumPosition(pos, probability/2, this);
    return right;
}

QuantumPositionTree::QuantumPosition * QuantumPositionTree::QuantumPosition::addLeft(const Position & pos) {
    left = new QuantumPosition(pos, probability/2, this);
    return left;
}

Position QuantumPositionTree::QuantumPosition::getData() const {
    return position;
}

QuantumPositionTree::QuantumPositionTree(const Position & position): root(new QuantumPosition(position, 1)), size_(1), leaves(1, root) {}

QuantumPositionTree::~QuantumPositionTree(){
    deleteRecursive(root);
}

void QuantumPositionTree::deleteRecursive(QuantumPosition * node){
    QuantumPosition * left_ = node->left;
    QuantumPosition * right_ = node->right;
    delete node;
    if(left_)
        deleteRecursive(left_);
    if(right_)
        deleteRecursive(right_);
}



void QuantumPositionTree::split(const Position & in_position, const Position & position_1, const Position & position_2) {
    auto it = findLeaveWithPosition(in_position);
    if (it == leaves.end())
        throw std::invalid_argument("no hay ninguna hoja con esa posicion");
    QuantumPosition *left = (*it)->addLeft(position_1);
    QuantumPosition *right = (*it)->addRight(position_2);
    it = leaves.erase(it);
    it = leaves.insert(it, left);
    leaves.insert(++it, right);
    size_ += 2;
}

uint32_t QuantumPositionTree::leavesSize() const {
    return leaves.size();
}

uint32_t QuantumPositionTree::size() const {
    return size_;
}

void QuantumPositionTree::measure(QuantumPosition * node) {
    if (!node)
        throw std::invalid_argument("el puntero apunta a null");
    if (node == root)
        throw std::invalid_argument("el puntero es la raiz");
    if (!isThere(root, node))
        throw std::invalid_argument("el puntero no pertenece al arbol");
    if (node->top->left == node) {
        node->top->left = nullptr;
    } else if(node->top->right == node) {
        node->top->right = nullptr;
    }
    deleteRecursive(root);
    node->top = nullptr;
    root = node;
    // TODO propagar probabilidad.
    leaves = std::vector<QuantumPosition *>();
    size_ = 0;
    updateSizeAndLeaves(root);
}

void QuantumPositionTree::updateSizeAndLeaves(QuantumPosition * node) {
    if (!node)
        return;
    if (!node->left && !node->right)
        leaves.push_back(node);
    size_++;
    updateSizeAndLeaves(node->left);
    updateSizeAndLeaves(node->right);
}

std::vector<Position> QuantumPositionTree::getLeavesData(){
    std::vector<Position> leaves_data;
    leaves_data.reserve(leaves.size());
    for (auto & leave : leaves){
        leaves_data.push_back(leave->getData());
    }
    return leaves_data;
}

bool QuantumPositionTree::isThere(QuantumPosition * now_node, QuantumPosition * search){
    if (!now_node || !search)
        return false;
    if (now_node == search)
        return true;
    if (isThere(now_node->left, search))
        return true;
    if (isThere(now_node->right, search))
        return true;
    return false;
}

void QuantumPositionTree::move(const Position & initial, const Position & final) {
    auto it = findLeaveWithPosition(initial);
    if (it != leaves.end())
        (*it)->position = final;
    else
        throw std::invalid_argument("la posicion no se encuentra en una hoja");
}

std::vector<QuantumPositionTree::QuantumPosition *>::iterator QuantumPositionTree::findLeaveWithPosition(const Position &position) {
    auto it = leaves.begin();
    for (; it != leaves.end(); ++it){
        if ((*it)->position == position)
            break;
    }
    return it;
}
