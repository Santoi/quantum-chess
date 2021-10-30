#include <gtest/gtest.h>
#include "../src/chessman.h"

TEST(Chessman, Value) {
    Chessman chessman(5);
    EXPECT_EQ(chessman.getValue(), 5);
}