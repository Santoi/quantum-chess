#include "pseudo_random_coin.h"
#include <ctime>

// TODO ver que usar. Usar algun mixer.
// TODO ver la c++ 11 library. IMPORTANTE!!
// TODO mutex?
PseudoRandomCoin::PseudoRandomCoin(): engine(time(nullptr)) {}

PseudoRandomCoin::PseudoRandomCoin(uint seed): engine(seed) {}

bool PseudoRandomCoin::flip() {
    uint number = engine();
    return number < (std::minstd_rand::max() - std::minstd_rand::min()) / 2;
}
