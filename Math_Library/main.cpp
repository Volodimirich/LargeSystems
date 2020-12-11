//
// Created by voland on 09.12.2020.
//
#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "Functions.h"
#include "Factory.h"



using TFunctionPtr = std::shared_ptr<TFunction>;

int main(int argc, char *argv[])
{

    FuncFactory fact;
    auto fun_1 = fact.Create("power", 3);
    auto fun_2 = fact.Create("const", 27);

    auto p = fun_1 - fun_2;
    std::cout << p->ToString();
    std::cout << gradient_descent(p,1000);

//    auto fun_2 = Factory.Create("polynomial", {7, 0, 3, 15, 20});
//    std::cout << fun_2->Deriv(2) << std::endl;
//
//    auto fun_3 = Factory.Create("ident");
//    std::cout << fun_3->Deriv(2) << std::endl;
//
//    auto fun_4 = Factory.Create("exp", 2);
//    std::cout << fun_4->Deriv(2) << std::endl;
//
//    auto fun_5 = Factory.Create("const", 2);
//    std::cout << fun_5->Deriv(2) << std::endl;


//    auto f = Factory.Create("power", 2); // PowerFunc x^2 cont.push_back(f); auto g =
//    cont.push_back(f);
//    auto g = Factory.Create("polynomial", {7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3
//    cont.push_back(g);
//    for (const auto ptr : cont) {
//        std::cout << ptr->ToString() << " for x = 10 is " << (*ptr)(10) << std::endl;
//    }
//    auto p = f + g;
//    std::cout << (*p).Deriv(1) << " " << (*f).Deriv(3) << std::endl;
//    std::cout << (*p)(10) << std::endl;
//    auto fun_2 = Factory.Create("polynomial", {0, 1, -2.3});
}