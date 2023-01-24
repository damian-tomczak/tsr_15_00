#include <gtest/gtest.h>

#include "core/resultparser.h"

TEST(DummyTests, Dummytest)
{
    const auto multiplication = 28*10*2000;
    const auto expected = 560000;
    ASSERT_EQ(expected, multiplication);
}

TEST(Basic, Adding)
{
    ResultParser parser;
    auto result = parser.orderResult("print(subtract(5,2))");
    ASSERT_EQ("3", result);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}