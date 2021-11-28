#include "pseudo_random_coin.h"
#include <ctime>
#include <iostream>

PseudoRandomCoin::PseudoRandomCoin() : engine(clock() * time(nullptr)),
                                       random(true) {}

PseudoRandomCoin::PseudoRandomCoin(bool random_) : engine(), random(random_) {
}

bool PseudoRandomCoin::flip() {
  if (!random)
    return true;
  uint64_t number = engine();
  return number % 2;
}
