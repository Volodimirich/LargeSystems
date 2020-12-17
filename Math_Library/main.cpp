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
    FuncFactory Factory;
    std::vector <TFunctionPtr> cont;


    auto f = Factory.Create("power", 2); // PowerFunc x^2 cont.push_back(f); auto g =
    cont.push_back(f);
    auto g = Factory.Create("polynomial", {7, 0, 3, 15}); // TPolynomial 7 + 3*x^2 + 15*x^3
    cont.push_back(g);
    for (const auto& ptr : cont) {
        std::cout << ptr->ToString() << " for x = 10 is " << (*ptr)(10) << std::endl;
    }
    auto p = f + g;
    std::cout << (*p).Deriv(1) << " " << (*f).Deriv(3) << std::endl;
    std::cout << (*p)(10) << std::endl;

    auto s = Factory.Create("exp", 3);
    std::cout << s->ToString() << std::endl;

//    auto l = s - Factory.Create("const", 27);
//    std::cout << gradient_descent(l, 1000, 0.001, 0.001);
//
    auto test = Factory.Create("polynomial", {1, 2, 1});
    std::cout << test->ToString() << " polynomial" << std::endl;

    auto t1 = Factory.Create("power",2);
    auto t2 = Factory.Create("power", 4);

    auto test2 = t1 / t2;
    std::cout << test2->ToString() << " test2" << std::endl;

    auto test3 = test2 / t1;
    std::cout << test3->ToString() << " test3" << std::endl;

    auto test4 = Factory.Create("power", 3);
    std::cout << test4->ToString() <<" power" << std::endl;
    //
    auto test5 = Factory.Create("exp", 3) - Factory.Create("const",9);
    std::cout << test5->ToString() << " test5" << std::endl;

    return 0;
}