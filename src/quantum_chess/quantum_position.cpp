#include <vector>
#include <algorithm>
#include "quantum_position.h"
#include "chess_exception.h"

QuantumPosition::QuantumPosition(uint8_t x, uint8_t y, double prob_, Chessman * chessman_):
                                 position(x, y), prob(prob_), entangled(), chessman(chessman_){
    if (prob > 1 || prob < 0)
        throw ChessException("probabilidad invalida");
}

QuantumPosition::QuantumPosition(const Position & position_, double prob_, std::list<QuantumPosition *> && list, Chessman * chessman_):
        position(position_), prob(prob_), entangled(std::move(list)), chessman(chessman_){
    if (prob > 1 || prob < 0)
        throw ChessException("probabilidad invalida");
}

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
    entangled = std::list<QuantumPosition*>();
}

std::list<QuantumPosition*> & QuantumPosition::getEntangled() {
    return entangled;
}

void QuantumPosition::measure() {
    if (chessman)
        chessman->measure(Position(*this));
    else throw std::runtime_error("se intenta medir una posicion no asignada a un chessman");
}

bool QuantumPosition::compareDoubleWithPrecision(double a, double b, double e) const {
    return std::abs(a - b) < e;
}

void QuantumPosition::setPosition(const Position & position_) {
    position = position_;
}

void QuantumPosition::addMeToEntangled() {
    if (entangled.empty())
        return;
    for (auto & entangled_qp : entangled)
        entangled_qp->entangled.push_back(this);
}

void QuantumPosition::deleteMeFromEntangled() {
    for (auto & other: entangled) {
        auto search_it = std::find(other->entangled.begin(),
                                   other->entangled.end(), this);
        if (search_it != other->entangled.end())
            other->entangled.erase(search_it);
    }
}

void QuantumPosition::deleteMeFromEntangled(QuantumPosition & other) {
    auto search_it = std::find(other.entangled.begin(),
                               other.entangled.end(), this);
    if (search_it != other.entangled.end())
        other.entangled.erase(search_it);
}

void QuantumPosition::deleteMeFromChessman() {
    std::list<QuantumPosition> chessman_positions = chessman->getAllPositions();
    auto search_it = std::find(chessman_positions.begin(), chessman_positions.end(), *this);
    if (search_it != chessman_positions.end())
        chessman_positions.erase(search_it);
}

void QuantumPosition::ifEntangledNotEntangledWithOtherThenUnEntangle(const QuantumPosition & other) {
    for (auto it = entangled.begin(); it != entangled.end(); ) {
        auto search_it = std::find(other.entangled.begin(), other.entangled.end(), *it);
        if (search_it == other.entangled.end()) {
            this->deleteMeFromEntangled(**it);
            it = entangled.erase(it);
            continue;
        }
        ++it;
    }
}

bool QuantumPosition::isEntangled(const QuantumPosition & other) {
    auto it = std::find(entangled.begin(), entangled.end(), &other);
    return it != entangled.end();
}

bool QuantumPosition::isThisChessman(const Chessman &chessman__) {
    return &chessman__ == chessman;
}


