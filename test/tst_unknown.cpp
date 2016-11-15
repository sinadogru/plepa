#include "gtest/gtest.h"

#include <plepa/unknown.h>


TEST(tst_unknown, test1)
{
    plepa::unkown a{5};

    EXPECT_EQ(*plepa::unknown_cast<int>(a), 5);
}

TEST(tst_unknown, test2)
{
    plepa::unkown a{5};

    auto ar = plepa::unknown_cast<int&>(a);
    if (ar)
        *ar = 3;

    EXPECT_EQ(*plepa::unknown_cast<int>(a), 3);
}
