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
    ASSERT_EQ("x^2", fun_1->ToString());
}

TEST(Functions, TestPolynomialString) {
    FuncFactory fact;
    auto fun_1 = fact.Create("polynomial", {7, 11, 0,  3, 1, 20});
    ASSERT_EQ("7 + 11*x + 3*x^3 + x^4 + 20*x^5", fun_1->ToString());
}


TEST(Functions, TestIdentString) {
    FuncFactory fact;
    auto fun_1 = fact.Create("ident");
    ASSERT_EQ("x", fun_1->ToString());
}

TEST(Functions, TestExpString) {
    FuncFactory fact;
    auto fun_1 = fact.Create("exp", 2);
    ASSERT_EQ("2^x", fun_1->ToString());
}


TEST(Functions, TestConstString) {
    FuncFactory fact;
    auto fun_1 = fact.Create("const", 2);
    ASSERT_EQ("2", fun_1->ToString());
}

TEST(Derivative, TestPowerDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("power", 2);
    ASSERT_EQ(4, fun_1->Deriv(2));
}

TEST(Derivative, TestPolynomialDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("polynomial", {7, 0, 3, 15, 20});
    ASSERT_EQ(832, fun_1->Deriv(2));
}


TEST(Derivative, TestIdentDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("ident");
    ASSERT_EQ(1, fun_1->Deriv(2));
}

TEST(Derivative, TestExpDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("exp", 2);
    ASSERT_NEAR(2.77259, fun_1->Deriv(2), 0.0001);
}

TEST(Derivative, TestConstDeriv) {
    FuncFactory fact;
    auto fun_1 = fact.Create("const", 2);
    ASSERT_EQ(0, fun_1->Deriv(2));
}

TEST(Arifmethic, TestConstDerivSum) {
    FuncFactory fact;
    auto fun_1 = fact.Create("const", 2);

    auto fun_2 = fact.Create("const", 5);

    auto fun_3 = fact.Create("const", 20);

    auto fun_4 = fact.Create("const", 11);

    auto p = fun_1 + fun_2 + fun_3 + fun_4;
    ASSERT_EQ("2 + 5 + 20 + 11", p->ToString());

}


TEST(Arifmethic, TestIdentArifmSum) {
    FuncFactory fact;
    auto fun_1 = fact.Create("ident");

    auto fun_2 = fact.Create("ident");

    auto fun_3 = fact.Create("ident");

    auto fun_4 = fact.Create("ident");

    auto p = fun_1 + fun_2 + fun_3 + fun_4;
    ASSERT_EQ("x + x + x + x", p->ToString());

}

TEST(Arifmethic, TestExpArifSum) {
    FuncFactory fact;
    auto fun_1 = fact.Create("exp", 11.42);

    auto fun_2 = fact.Create("exp", 5);

    auto fun_3 = fact.Create("exp", 20.5);

    auto fun_4 = fact.Create("exp", 11);

    auto p = fun_1 + fun_2 + fun_3 + fun_4;
    ASSERT_EQ("11.420^x + 5^x + 20.500^x + 11^x", p->ToString());

}

TEST(Arifmethic, TestPowerArifm) {
    FuncFactory fact;
    auto fun_1 = fact.Create("power", 4.2);

    auto fun_2 = fact.Create("power", 5);

    auto fun_3 = fact.Create("power", 20.14);

    auto fun_4 = fact.Create("power", 11);

    auto p = fun_1 + fun_2 + fun_3 + fun_4;
    ASSERT_EQ("x^4.200 + x^5 + x^20.140 + x^11", p->ToString());

}


TEST(Arifmethic, TestPolynomialArifmSum) {
    FuncFactory fact;
    auto fun_1 = fact.Create("polynomial", {7, 0, 11});

    auto fun_2 = fact.Create("polynomial", {4, 2, 3, 20});

    auto fun_3 = fact.Create("polynomial", {11.4, 22.3, 14});

    auto fun_4 = fact.Create("polynomial", {7});

    auto p = fun_1 + fun_2 + fun_3 + fun_4;
    ASSERT_EQ("7 + 11*x^2 + 4 + 2*x + 3*x^2 + 20*x^3 + 11.400 + 22.300*x + 14*x^2 + 7", p->ToString());

}

TEST(Arifmethic, TestConstDerivSub) {
    FuncFactory fact;
    auto fun_1 = fact.Create("const", 2);

    auto fun_2 = fact.Create("const", 5);

    auto fun_3 = fact.Create("const", 20);

    auto fun_4 = fact.Create("const", 11);

    auto p = fun_1 - fun_2 - fun_3 - fun_4;
    ASSERT_EQ("2 - 5 - 20 - 11", p->ToString());

}


TEST(Arifmethic, TestIdentArifmSub) {
    FuncFactory fact;
    auto fun_1 = fact.Create("ident");

    auto fun_2 = fact.Create("ident");

    auto fun_3 = fact.Create("ident");

    auto fun_4 = fact.Create("ident");

    auto p = fun_1 - fun_2 - fun_3 - fun_4;
    ASSERT_EQ("x - x - x - x", p->ToString());

}

TEST(Arifmethic, TestExpArifmSub) {
    FuncFactory fact;
    auto fun_1 = fact.Create("exp", 11.42);

    auto fun_2 = fact.Create("exp", 5);

    auto fun_3 = fact.Create("exp", 20.5);

    auto fun_4 = fact.Create("exp", 11);

    auto p = fun_1 - fun_2 - fun_3 - fun_4;
    ASSERT_EQ("11.420^x - 5^x - 20.500^x - 11^x", p->ToString());

}

TEST(Arifmethic, TestPowerArifmSub) {
    FuncFactory fact;
    auto fun_1 = fact.Create("power", 4.2);

    auto fun_2 = fact.Create("power", 5);

    auto fun_3 = fact.Create("power", 20.14);

    auto fun_4 = fact.Create("power", 11);

    auto p = fun_1 - fun_2 - fun_3 - fun_4;
    ASSERT_EQ("x^4.200 - x^5 - x^20.140 - x^11", p->ToString());

}


TEST(Arifmethic, TestPolynomialArifmSub) {
    FuncFactory fact;
    auto fun_1 = fact.Create("polynomial", {7, 0, 11});

    auto fun_2 = fact.Create("polynomial", {4, 2, 3, 20});

    auto fun_3 = fact.Create("polynomial", {11.4, 22.3, 14});

    auto fun_4 = fact.Create("polynomial", {7});

    auto p = fun_1 - fun_2 - fun_3 - fun_4;
    ASSERT_EQ("7 + 11*x^2 - 4 + 2*x + 3*x^2 + 20*x^3 - 11.400 + 22.300*x + 14*x^2 - 7", p->ToString());

}

TEST(Arifmethic, TestConstArifmMul) {
    FuncFactory fact;
    auto fun_1 = fact.Create("const", 2);

    auto fun_2 = fact.Create("const", 5);

    auto fun_3 = fact.Create("const", 20);

    auto fun_4 = fact.Create("const", 11);

    auto p = fun_1 * fun_2 * fun_3 * fun_4;
    ASSERT_EQ("2 * 5 * 20 * 11", p->ToString());

}


TEST(Arifmethic, TestIdentArifmMul) {
    FuncFactory fact;
    auto fun_1 = fact.Create("ident");

    auto fun_2 = fact.Create("ident");

    auto fun_3 = fact.Create("ident");

    auto fun_4 = fact.Create("ident");

    auto p = fun_1 * fun_2 * fun_3 * fun_4;
    ASSERT_EQ("x * x * x * x", p->ToString());

}

TEST(Arifmethic, TestExpArifmMul) {
    FuncFactory fact;
    auto fun_1 = fact.Create("exp", 11.42);

    auto fun_2 = fact.Create("exp", 5);

    auto fun_3 = fact.Create("exp", 20.5);

    auto fun_4 = fact.Create("exp", 11);

    auto p = fun_1 * fun_2 * fun_3 * fun_4;
    ASSERT_EQ("11.420^x * 5^x * 20.500^x * 11^x", p->ToString());

}

TEST(Arifmethic, TestPowerArifmMul) {
    FuncFactory fact;
    auto fun_1 = fact.Create("power", 4.2);

    auto fun_2 = fact.Create("power", 5);

    auto fun_3 = fact.Create("power", 20.14);

    auto fun_4 = fact.Create("power", 11);

    auto p = fun_1 * fun_2 * fun_3 * fun_4;
    ASSERT_EQ("x^4.200 * x^5 * x^20.140 * x^11", p->ToString());

}


TEST(Arifmethic, TestPolynomialArifmMul) {
    FuncFactory fact;
    auto fun_1 = fact.Create("polynomial", {7, 0, 11});

    auto fun_2 = fact.Create("polynomial", {4, 2, 3, 20});

    auto fun_3 = fact.Create("polynomial", {11.4, 22.3, 14});

    auto fun_4 = fact.Create("polynomial", {7});

    auto p = fun_1 * fun_2 * fun_3 * fun_4;
    ASSERT_EQ("7 + 11*x^2 * 4 + 2*x + 3*x^2 + 20*x^3 * 11.400 + 22.300*x + 14*x^2 * 7", p->ToString());

}

TEST(Arifmethic, TestConstArifmDel) {
    FuncFactory fact;
    auto fun_1 = fact.Create("const", 2);

    auto fun_2 = fact.Create("const", 5);

    auto fun_3 = fact.Create("const", 20);

    auto fun_4 = fact.Create("const", 11);

    auto p = fun_1 / fun_2 / fun_3 / fun_4;
    ASSERT_EQ("2 / 5 / 20 / 11", p->ToString());

}


TEST(Arifmethic, TestIdentArifmDel) {
    FuncFactory fact;
    auto fun_1 = fact.Create("ident");

    auto fun_2 = fact.Create("ident");

    auto fun_3 = fact.Create("ident");

    auto fun_4 = fact.Create("ident");

    auto p = fun_1 / fun_2 / fun_3 / fun_4;
    ASSERT_EQ("x / x / x / x", p->ToString());

}

TEST(Arifmethic, TestExpArifmDel) {
    FuncFactory fact;
    auto fun_1 = fact.Create("exp", 11.42);

    auto fun_2 = fact.Create("exp", 5);

    auto fun_3 = fact.Create("exp", 20.5);

    auto fun_4 = fact.Create("exp", 11);

    auto p = fun_1 / fun_2 / fun_3 / fun_4;
    ASSERT_EQ("11.420^x / 5^x / 20.500^x / 11^x", p->ToString());

}

TEST(Arifmethic, TestPowerArifmDel) {
    FuncFactory fact;
    auto fun_1 = fact.Create("power", 4.2);

    auto fun_2 = fact.Create("power", 5);

    auto fun_3 = fact.Create("power", 20.14);

    auto fun_4 = fact.Create("power", 11);

    auto p = fun_1 / fun_2 / fun_3 / fun_4;
    ASSERT_EQ("x^4.200 / x^5 / x^20.140 / x^11", p->ToString());

}


TEST(Arifmethic, TestPolynomialArifmDel) {
    FuncFactory fact;
    auto fun_1 = fact.Create("polynomial", {7, 0, 11});

    auto fun_2 = fact.Create("polynomial", {4, 2, 3, 20});

    auto fun_3 = fact.Create("polynomial", {11.4, 22.3, 14});

    auto fun_4 = fact.Create("polynomial", {7});

    auto p = fun_1 / fun_2 / fun_3 / fun_4;
    ASSERT_EQ("7 + 11*x^2 / 4 + 2*x + 3*x^2 + 20*x^3 / 11.400 + 22.300*x + 14*x^2 / 7", p->ToString());

}

TEST(ErrorTests, TestOperationsErrors) {
    FuncFactory fact;
    auto fun = fact.Create("exp", 2);
    ASSERT_THROW(fun + "Hello", std::logic_error);
    ASSERT_THROW("Darkness" + fun, std::logic_error);
    ASSERT_THROW(fun + 42, std::logic_error);
    ASSERT_THROW(fun - 42, std::logic_error);
    ASSERT_THROW(42 + fun, std::logic_error);
    ASSERT_THROW(42 - fun, std::logic_error);
    ASSERT_THROW("My" - fun, std::logic_error);
    ASSERT_THROW(fun - "Old", std::logic_error);
    ASSERT_THROW(fun * "Friend", std::logic_error);
    ASSERT_THROW("I" * fun, std::logic_error);
    ASSERT_THROW(fun * 1, std::logic_error);
    ASSERT_THROW(2.2 * fun, std::logic_error);
    ASSERT_THROW(fun / "Come", std::logic_error);
    ASSERT_THROW("To Talk with you again" / fun, std::logic_error);
    ASSERT_THROW(fun / 1, std::logic_error);
    ASSERT_THROW(2.2 / fun, std::logic_error);
}

TEST(ErrorTests, TestCreationErrors) {
    FuncFactory fact;
    ASSERT_THROW(fact.Create("exp", {2}), std::logic_error);
    ASSERT_THROW(fact.Create("power", {2}), std::logic_error);
    ASSERT_THROW(fact.Create("ident", {2}), std::logic_error);
    ASSERT_THROW(fact.Create("exp", {2}), std::logic_error);
}



TEST(GradientDescentTest, TestPolynomialFunction) {
    FuncFactory fact;
    auto fun_1 = fact.Create("polynomial", {1, -2, 1});

    ASSERT_NEAR(1, gradient_descent(fun_1, 1000), 0.0001);
}

TEST(GradientDescentTest, TestExpFunction) {
    FuncFactory fact;
    auto fun_1 = fact.Create("exp", 3);
    auto fun_2 = fact.Create("const", 3);

    auto p = fun_1 - fun_2;
    ASSERT_EQ("3^x - 3", p->ToString());
    ASSERT_NEAR(1, gradient_descent(p, 1000), 0.0001);

}

TEST(GradientDescentTest, TestPowerFunction) {
    FuncFactory fact;
    auto fun_1 = fact.Create("power", 3);
    auto fun_2 = fact.Create("const", 27);

    auto p = fun_1 - fun_2;
    ASSERT_EQ("x^3 - 27", p->ToString());
//    ASSERT_NEAR(3, gradient_descent(p, 1000), 0.0001);

}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}