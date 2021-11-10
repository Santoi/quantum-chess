#include <vector>
#include "quantum_position.h"
#include "chess_exception.h"

QuantumPosition::QuantumPosition(): position(), prob(1), entangled(), chessman(nullptr) {}

QuantumPosition::QuantumPosition(Chessman * chessman_): position(), prob(1), entangled(), chessman(chessman_) {}

QuantumPosition::QuantumPosition(uint8_t x, uint8_t y, double prob_, Chessman * chessman_):
                                 position(x, y), prob(prob_), entangled(), chessman(chessman_){
    if (prob > 1 || prob < 0)
        throw ChessException("probabilidad invalida");
}

QuantumPosition::QuantumPosition(const Position & position_, double prob_, std::list<QuantumPosition *> & list, Chessman * chessman_):
        position(position_), prob(prob_), entangled(list), chessman(chessman_){
    if (prob > 1 || prob < 0)
        throw ChessException("probabilidad invalida");
}

QuantumPosition::QuantumPosition(const Position &position_, Chessman * chessman_):
                                 position(position_), prob(1), chessman(chessman_) {}

QuantumPosition::QuantumPosition(const Position & position_, double prob_, Chessman * chessman_):
                                 position(position_), prob(prob_), chessman(chessman_) {
    if (prob > 1 || prob < 0)
        throw ChessException("probabilidad invalida");
}

uint8_t QuantumPosition::x() const {
    return position.x();
}

uint8_t QuantumPosition::y() const {
    return position.y();
}

double QuantumPosition::getProb() const{
    return prob;
}

bool QuantumPosition::operator==(const QuantumPosition &other) const {
    return position == other.position && compareDoubleWithPrecision(prob, other.prob, PRECISION_PROB);
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

void QuantumPosition::setProb(double prob_){
    if (prob < 0 || prob > 1)
        throw ChessException("probabilidad invalida");
    prob = prob_;
}

void QuantumPosition::entangle(QuantumPosition & other) {
    entangled.push_back(&other);
}

void QuantumPosition::unentangle() {
    entangled = std::list<QuantumPosition * >();
}

std::list<QuantumPosition * > & QuantumPosition::getEntangled() {
    return entangled;
}

void QuantumPosition::measure() {
    if(chessman)
        chessman->measure(Position(*this));
    // TODO ver esto.
    else throw std::runtime_error("se intenta medir una posicion no asignada a un chessman");
}

bool QuantumPosition::compareDoubleWithPrecision(double a, double b, double e) const {
    return std::abs(a - b) < e;
}

