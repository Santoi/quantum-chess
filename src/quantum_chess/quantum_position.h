#ifndef QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H
#define QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H

#include <list>
#include "position.h"

class Position;

// TODO pdria ser hija de Position?? (no se si vale mucho la pena)

class QuantumPosition {
    Position position;
    double prob;
    std::list<QuantumPosition *> entangled;

public:
    QuantumPosition();

    explicit QuantumPosition(const Position &position_);

    QuantumPosition(uint8_t x, uint8_t y, double prob_);

    QuantumPosition(const Position &position_, double prob_);

    bool operator==(const QuantumPosition &other) const;

    bool operator==(const Position &other) const;

    bool operator!=(const QuantumPosition &other) const;

    bool operator!=(const Position &other) const;

    uint8_t x() const;

    uint8_t y() const;

    double getProb() const;

    void setProb(double prob_);

    void entangle(QuantumPosition *other);
};


#endif //QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H
