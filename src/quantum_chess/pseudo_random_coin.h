#ifndef QUANTUM_CHESS_PROJ_PSEUDORANDOM_H
#define QUANTUM_CHESS_PROJ_PSEUDORANDOM_H

#include <mutex>
#include <random>

// Clase protegida:
// The function accesses and modifies internal state objects, which may cause
//data races with concurrent calls to rand or srand.
class PseudoRandomCoin {
    std::minstd_rand engine;

public:
    PseudoRandomCoin();

    explicit PseudoRandomCoin(uint seed);

    bool flip();
};


#endif //QUANTUM_CHESS_PROJ_PSEUDORANDOM_H
