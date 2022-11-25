#include "gtest/gtest.h"
#include "../cstring_util.h"

TEST(CStringUtilTestSuite, EqualLast) {
    EXPECT_EQ(cstring_util::EqualLast("xyz", "xyz"), true);
    EXPECT_EQ(cstring_util::EqualLast("something.xyz", ".xyz"), true);
    EXPECT_EQ(cstring_util::EqualLast("something.xyz", ".abc"), false);
}
