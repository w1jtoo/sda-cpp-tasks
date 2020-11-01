#include "entry_point.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

/**
  * Write your OWN tests here.
  * Coverage of these tests will be measured.
 **/


namespace Example {
    TEST(Public, MyTest1) {
        ASSERT_EQ(.0, evaluate("0"));
    }
/*
    TEST(Public, MyTest2) {
        ASSERT_EQ(1001, sum(1001, 0));
    }*/
}
