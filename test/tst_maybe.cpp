#include "gtest/gtest.h"

#include <plepa/maybe.h>


TEST(tst_maybe, test1)
{
    plepa::maybe<int> x;

    EXPECT_FALSE(x);
    EXPECT_EQ(x, plepa::nothing);
}

TEST(tst_maybe, test2)
{
    plepa::maybe<int> x{3};

    EXPECT_TRUE(x);
    EXPECT_EQ(x, plepa::just);
    EXPECT_EQ(*x, 3);
}

TEST(tst_maybe, test3)
{
    plepa::maybe<int> x{3};

    if (x)
        *x = 5;

    EXPECT_EQ(*x, 5);
}
