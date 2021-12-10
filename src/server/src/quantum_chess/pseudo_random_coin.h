#ifndef QUANTUM_CHESS_PROJ_PSEUDORANDOM_H
#define QUANTUM_CHESS_PROJ_PSEUDORANDOM_H

#include <random>

// Class used to generate a random boolean whit fifty-fifty probability.
class PseudoRandomCoin {
  std::mt19937_64 engine;
  bool random;

public:
  PseudoRandomCoin();

  // Constructor. If random_ is false flip() return always true.
  explicit PseudoRandomCoin(bool random_);

  // Return a boolean with fifty-fifty probability.
  bool flip();
};


#endif //QUANTUM_CHESS_PROJ_PSEUDORANDOM_H
