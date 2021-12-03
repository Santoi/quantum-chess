#include <gtest/gtest.h>
#include <vector>
#include "../src/server/src/quantum_chess/pseudo_random_coin.h"

TEST(PseudoRandomCoin, FiftyFiftyWithSameObject) {
  int runs = 100000;
  PseudoRandomCoin random;
  double mean = 0;
  for (int i = 0; i < runs; i++) {
    mean += random.flip();
  }
  mean /= runs;
  EXPECT_TRUE(mean > 0.49 && mean < 0.51);
}

TEST(PseudoRandomCoin, FiftyFiftyWithFirstRunOfDifferentObjects) {
  int runs = 100000;
  double mean = 0;
  for (int i = 0; i < runs; i++) {
    PseudoRandomCoin random;
    mean += random.flip();
  }
  mean /= runs;
  EXPECT_TRUE(mean > 0.49 && mean < 0.51);
}
