#ifndef QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H
#define QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H

#include <list>
#include "position.h"
//#include "chessman/chessman.h"

#define PRECISION_PROB 1.5258e-5

class Position;

class Chessman;

class QuantumPosition {
  Position position;
  double prob;
  Chessman *chessman;

public:
  QuantumPosition(const Position &position_, double prob_,
                  Chessman *chessman_ = nullptr);

  QuantumPosition(uint8_t x, uint8_t y, double prob_,
                  Chessman *chessman_ = nullptr);

  bool operator==(const QuantumPosition &other) const;

  bool operator==(const Position &other) const;

  bool operator!=(const QuantumPosition &other) const;

  bool operator!=(const Position &other) const;

  uint8_t x() const;

  uint8_t y() const;

  double getProb() const;

  void setProb(double prob_);

  bool compareDoubleWithPrecision(double a, double b, double e) const;

  void setPosition(const Position &position_);

  void measure();

  bool isMyChessman(const Chessman &chessman_) const;

  const Chessman &getChessman();
};


#endif //QUANTUM_CHESS_PROJ_QUANTUM_POSITION_H
