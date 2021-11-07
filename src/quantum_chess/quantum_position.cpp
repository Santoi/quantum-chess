#include "quantum_position.h"
#include "chess_exception.h"

QuantumPosition::QuantumPosition(): position(), prob(1) {}

QuantumPosition::QuantumPosition(uint8_t x, uint8_t y, double prob_):
                                 position(x, y), prob(prob_){
    if (prob > 1 || prob < 0)
        throw ChessException("probabilidad invalida");
}

QuantumPosition::QuantumPosition(const Position &position_):
                                 position(position_), prob(1) {}

QuantumPosition::QuantumPosition(const Position & position_, double prob_):
                                 position(position_), prob(prob_) {
    if (prob > 1 || prob < 0)
        throw ChessException("probabilidad invalida");
}

uint8_t QuantumPosition::x() const {
    return position.x();
}

uint8_t QuantumPosition::y() const {
    return position.y();
}

double QuantumPosition::getProbability() const{
    return prob;
}

bool QuantumPosition::operator==(const QuantumPosition &other) const {
    return position == other.position && prob == other.prob;
}

bool QuantumPosition::operator!=(const QuantumPosition &other) const {
    return !(*this == other);
}

bool QuantumPosition::operator==(const Position &other) const {
    return other == position;
}

bool QuantumPosition::operator!=(const Position &other) const {
    return !(*this == other);
}

