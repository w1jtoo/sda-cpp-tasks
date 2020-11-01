#include "entry_point.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(Public, Plus) {
    ASSERT_DOUBLE_EQ(4, evaluate("2 + 2"));
}

TEST(Public, Minus) {
    ASSERT_DOUBLE_EQ(2, evaluate("7 - 5"));
}

TEST(Public, Multiply) {
    ASSERT_DOUBLE_EQ(90, evaluate("9 * 10"));
}

TEST(Public, Divide) {
    ASSERT_DOUBLE_EQ(6, evaluate("66 / 11"));
}

TEST(Public, Parentheses) {
    ASSERT_DOUBLE_EQ(-2, evaluate("2 * (3 - 4)"));
}

TEST(Public, SyntaxError) {
    ASSERT_THROW(evaluate("2 +"), std::runtime_error);
}

TEST(Public, DivisionByZero) {
    ASSERT_THROW(evaluate("1 / 0"), std::runtime_error);
}
