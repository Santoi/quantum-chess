#ifndef QUANTUM_CHESS_PROJ_POSITION_H
#define QUANTUM_CHESS_PROJ_POSITION_H

#include <cstdint>

class Position {
    uint8_t x_, y_;

public:
    Position(uint8_t x_, uint8_t y_);

    uint8_t x() const;
    uint8_t y() const;
};


#endif //QUANTUM_CHESS_PROJ_POSITION_H
