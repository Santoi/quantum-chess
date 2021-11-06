#ifndef QUANTUM_CHESS_PROJ_POSITION_H
#define QUANTUM_CHESS_PROJ_POSITION_H

#include <cstdint>
#include <iostream>

/* Clase que representa una posicion,
 * con coordenadas x e y. */
class Position {
    uint8_t x_, y_;

public:
    Position();

    Position(uint8_t x_, uint8_t y_);

    Position(const Position & orig) = default;
    
    Position & operator=(const Position & orig);
    
    bool operator==(const Position & other) const;
    
    bool operator!=(const Position & other) const;

	// Devuelve la coordenada x.
    uint8_t x() const;
    
    // Devuelve la coordenada y.
    uint8_t y() const;

    friend bool operator<(const Position & a, const Position & b);

    friend std::ostream & operator<<(std::ostream & os,
                                     const Position & position);
};




#endif //QUANTUM_CHESS_PROJ_POSITION_H
