#include <gtest/gtest.h>
#include <iostream>
#include <QDebug>

#include "core/resultparser.hpp"

TEST(DummyTests, Dummytest)
{
    const auto multiplication = 28*10*2000;
    const auto expected = 560000;
    ASSERT_EQ(expected, multiplication);
}

TEST(Basic, Adding)
{
    std::string_view firstResult{};
    ResultParser parser;
    auto output = parser.orderResult("print(add(2,2))").toStdString();
    auto pos = output.find("\r\n");
    if (pos != std::string::npos)
    {
        firstResult = { output.begin(), output.begin() + pos };
    }
    ASSERT_EQ("4", firstResult);
}

TEST(Basic, Subtracting)
{
    std::string_view firstResult{};
    ResultParser parser;
    auto output = parser.orderResult("print(subtract(5,2))").toStdString();
    auto pos = output.find("\r\n");
    if (pos != std::string::npos)
    {
        firstResult = { output.begin(), output.begin() + pos };
    }
    ASSERT_EQ("3", firstResult);
}

TEST(Basic, ModuloOperation)
{
    std::string_view firstResult{};
    ResultParser parser;
    auto output = parser.orderResult("print(modulo(1,5))").toStdString();
    auto pos = output.find("\r\n");
    if (pos != std::string::npos)
    {
        firstResult = { output.begin(), output.begin() + pos };
    }
    ASSERT_EQ("1", firstResult);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}