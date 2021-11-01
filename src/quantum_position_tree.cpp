#include "quantum_position_tree.h"
#include <algorithm>
#include <stdexcept>

QuantumPosition::QuantumPosition(const int &data_, const double & probability_): data(data_), probability(probability_), top(nullptr), left(nullptr), right(nullptr) {}

QuantumPosition::QuantumPosition(const int & data_, const double & probability_, QuantumPosition * top_): data(data_), probability(probability_), top(top_), left(nullptr), right(nullptr) {}

QuantumPosition::~QuantumPosition() = default;

QuantumPosition * QuantumPosition::addRight(const int &data) {
    right = new QuantumPosition(data, probability/2, this);
    return right;
}

QuantumPosition * QuantumPosition::addLeft(const int &data) {
    left = new QuantumPosition(data, probability/2, this);
    return left;
}

int QuantumPosition::getData() const {
    return data;
}

QuantumPositionTree::QuantumPositionTree(const int & data): root(new QuantumPosition(data, 1)), size_(1), leaves(1, root) {}

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

std::pair<QuantumPosition *, QuantumPosition *> QuantumPositionTree::split(QuantumPosition * node, const int & data_1, const int & data_2) {
    auto it = std::find(leaves.begin(), leaves.end(), node);
    if (it == leaves.end())
        throw std::invalid_argument("el nodo no es una hoja");
    QuantumPosition *left = node->addLeft(data_1);
    QuantumPosition *right = node->addRight(data_2);
    it = leaves.erase(it);
    it = leaves.insert(it, left);
    leaves.insert(++it, right);
    size_ += 2;
    return {left, right};
}

uint32_t QuantumPositionTree::leavesSize() const {
    return leaves.size();
}

uint32_t QuantumPositionTree::size() const {
    return size_;
}

QuantumPosition * QuantumPositionTree::getRoot() const{
    return root;
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
    leaves = std::vector<const QuantumPosition *>();
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

std::vector<int> QuantumPositionTree::getLeavesData(){
    std::vector<int> leaves_data;
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

void QuantumPositionTree::move(QuantumPosition *node, const int & data) {
    node->data = data;
}
