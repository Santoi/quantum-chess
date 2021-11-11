#ifndef QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H
#define QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H

#include <list>
#include "position.h"
#include "chessman/chessman.h"

#define PRECISION_PROB 1.5258e-5

class Position;
class Chessman;

// TODO pdria ser hija de Position?? (no se si vale mucho la pena)

class QuantumPosition {
    QuantumPosition();

    Position position;
    double prob;
    std::list<QuantumPosition *> entangled;
    Chessman * chessman;

public:
    explicit QuantumPosition(Chessman * chessman_ = nullptr);

    explicit QuantumPosition(const Position &position_, Chessman * chessman_ = nullptr);

    QuantumPosition(const Position & position_, double prob_, Chessman * chessman_ = nullptr);

    QuantumPosition(uint8_t x, uint8_t y, double prob_, Chessman *chessman_ = nullptr);

    QuantumPosition(const Position &position_, double prob_,
                    std::list<QuantumPosition *> &list, Chessman *chessman_);

    bool operator==(const QuantumPosition &other) const;

    bool operator==(const Position &other) const;

    bool operator!=(const QuantumPosition &other) const;

    bool operator!=(const Position &other) const;

    uint8_t x() const;

    uint8_t y() const;

    double getProb() const;

    void setProb(double prob_);

    void unentangle();

    std::list<QuantumPosition *> &getEntangled();

    void entangle(QuantumPosition & other);

    void measure();

    bool compareDoubleWithPrecision(double a, double b, double e) const;

    void setPosition(const Position &position_);

    void addToEntangled(QuantumPosition & new_qp);

    void deleteMeFromEntangled();

    void deleteMeFromChessman();

    void deleteMeFromEntangled(QuantumPosition *quantum);

    const Chessman *getChessman();
};


#endif //QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H
