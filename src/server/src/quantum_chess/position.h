#ifndef QUANTUM_CHESS_PROJ_POSITION_H
#define QUANTUM_CHESS_PROJ_POSITION_H

#include <cstdint>
#include <iostream>

class QuantumPosition;

/* Clase que representa una posicion,
 * con coordenadas x e y. */
class Position {
  uint8_t x_, y_;

public:
  Position();

  Position(uint8_t x, uint8_t y);

  Position(const Position &orig) = default;

  explicit Position(const QuantumPosition &position);

  Position &operator=(const Position &orig) = default;

  bool operator==(const Position &other) const;

  bool operator!=(const Position &other) const;

  bool operator==(const QuantumPosition &other) const;

  bool operator!=(const QuantumPosition &other) const;

  // Devuelve la coordenada x.
  uint8_t x() const;

  // Devuelve la coordenada y.
  uint8_t y() const;

  friend bool operator<(const Position &a, const Position &b);

  friend std::ostream &operator<<(std::ostream &os,
                                  const Position &position);

  std::string print() const;
};


#endif //QUANTUM_CHESS_PROJ_POSITION_H
