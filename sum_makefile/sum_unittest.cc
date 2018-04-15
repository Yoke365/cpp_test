#include <limits.h>
#include "gtest/gtest.h"

#include "sum.h"

namespace {

TEST(sumtest, Positive) {
  EXPECT_EQ(3, sum(1, 2));
}

}  // namespace
