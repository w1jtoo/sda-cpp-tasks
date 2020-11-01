#include "entry_point.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(PublicAdvanced, Power) {
    ASSERT_DOUBLE_EQ(1024, evaluate("2^10"));
}

TEST(PublicAdvanced, AllTogether) {
    ASSERT_DOUBLE_EQ(0.01162993295018809, evaluate("1 / (sin(3*pi/2) + 2^3 * 4*e)"));
}
