#include "src/includefile.h"

#include <gtest/gtest.h>

// this is incomplete
TEST(MyTestSuit, MyTestCase)
{
    ASSERT_FALSE(true);
}

TEST(testname, testcase)
{
    Coordinate cord = Coordinate(2, 8);
    ASSERT_EQ(cord.x, 2);
}