#ifndef QUANTUM_CHESS_PROJ_PSEUDORANDOM_H
#define QUANTUM_CHESS_PROJ_PSEUDORANDOM_H

#include <mutex>
#include <random>

// Clase protegida:
// The function accesses and modifies internal state objects, which may cause
//data races with concurrent calls to rand or srand.
class PseudoRandomCoin {
  std::mt19937_64 engine;
  bool random;

public:
  PseudoRandomCoin();

  explicit PseudoRandomCoin(bool random_);

  bool flip();
};


#endif //QUANTUM_CHESS_PROJ_PSEUDORANDOM_H
