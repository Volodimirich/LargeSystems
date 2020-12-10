//
// Created by voland on 10.12.2020.
//


#include "Functions.h"
#include "Factory.h"
#include <gtest/gtest.h>
#include <typeinfo>
#include <cmath>




TEST(Functions, TestPowerString) {
    FuncFactory fact;
    auto fun_1 = fact.Create("power", 2);
    ASSERT_EQ("x^2.000000", fun_1->ToString());
}

TEST(Functions, TestPolynomialString) {
    FuncFactory fact;
    auto fun_1 = fact.Create("polynomial", {7, 0, 3, 15, 20});
    ASSERT_EQ("7.000000 + 3.000000*x^2 + 15.000000*x^3 + 20.000000*x^4", fun_1->ToString());
}


TEST(Functions, TestIdentString) {
    FuncFactory fact;
    auto fun_1 = fact.Create("ident");
    ASSERT_EQ("1.000000*x^1", fun_1->ToString());
}

TEST(Functions, TestExpString) {
    FuncFactory fact;
    auto fun_1 = fact.Create("exp", 2);
    ASSERT_EQ("2.000000^x", fun_1->ToString());
}


TEST(Functions, TestConstString) {
    FuncFactory fact;
    auto fun_1 = fact.Create("const", 2);
    ASSERT_EQ("2.000000", fun_1->ToString());
}

TEST(Functions, TestPowerDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("power", 2);
    ASSERT_EQ(4, fun_1->Deriv(2));
}

TEST(Functions, TestPolynomialDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("polynomial", {7, 0, 3, 15, 20});
    ASSERT_EQ(832, fun_1->Deriv(2));
}


TEST(Functions, TestIdentDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("ident");
    ASSERT_EQ(1, fun_1->Deriv(2));
}

TEST(Functions, TestExpDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("exp", 2);
    ASSERT_NEAR(2.77259, fun_1->Deriv(2), 0.0001);
}


TEST(Functions, TestConstDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("const", 2);
    ASSERT_EQ(0, fun_1->Deriv(2));
}

TEST(Arifmethic, TestConstDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("const", 2);
    ASSERT_EQ(0, fun_1->Deriv(2));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}