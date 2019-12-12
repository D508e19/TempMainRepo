#include "src/includefile.h"

#include <gtest/gtest.h>

// this is incomplete
TEST(MyTestSuit, MyTestCase)
{
    ASSERT_FALSE(false);
}

TEST(Coordinate_EQ_Test, Coordinate_EQ)
{
    Coordinate cord = Coordinate(2, 8);
    ASSERT_EQ(cord.x, 2);
}

TEST(MyTestSuit,test2){
    ASSERT_TRUE(true);
}