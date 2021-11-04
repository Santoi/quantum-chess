#ifndef QUANTUM_CHESS_PROJ_POSITION_H
#define QUANTUM_CHESS_PROJ_POSITION_H

#include <cstdint>
#include <iostream>

class Position {
    uint8_t x_, y_;

public:
    Position(uint8_t x_, uint8_t y_);

    Position(const Position & orig) = default;

    uint8_t x() const;
    uint8_t y() const;

    bool operator==(const Position & other) const;
    bool operator!=(const Position & other) const;
    Position & operator=(const Position & orig);

    friend bool operator<(const Position & a, const Position & b);

    friend std::ostream & operator<<(std::ostream & os, const Position & position);
};




#endif //QUANTUM_CHESS_PROJ_POSITION_H
