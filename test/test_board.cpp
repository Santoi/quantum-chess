#include <gtest/gtest.h>
#include <vector>
#include "../src/server/src/quantum_chess/board.h"

TEST(Board, FiftyFiftyWithSameObject) {
  int runs = 100000;
  Board board;
  double mean = 0;
  for (int i = 0; i < runs; i++) {
    mean += board.flipACoin();
  }
  mean /= runs;
  std::cout << mean << std::endl;
  EXPECT_TRUE(mean > 0.49 && mean < 0.51);
}

