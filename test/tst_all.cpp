#include "gtest/gtest.h"

#include <plepa/all.h>


TEST(tst_all, test1)
{
    plepa::all a{5};

    EXPECT_EQ(*plepa::all_cast<int>(a), 5);
}

TEST(tst_all, test2)
{
    plepa::all a{5};

    auto ar = plepa::all_cast<int&>(a);
    if (ar)
        *ar = 3;

    EXPECT_EQ(*plepa::all_cast<int>(a), 3);
}
