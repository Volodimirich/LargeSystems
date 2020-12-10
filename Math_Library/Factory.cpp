//
// Created by voland on 08.12.2020.
//

#include "Factory.h"

#include <memory>
#include <iostream>
#include <initializer_list>
#include <stdexcept>

std::shared_ptr<TFunction> FuncFactory::Create(std::string func, const std::initializer_list<double> &input )
{
    if (func == "polynomial")
        return std::shared_ptr<TFunction>(new Polinoms(input));
    else
        throw std::logic_error("Initializer list works only with polynomial function");
}

std::shared_ptr<TFunction> FuncFactory::Create(std::string func, double input) {
    if (func == "power")
        return std::shared_ptr<TFunction>(new PowerFunc(input));
    else if (func == "const")
        return std::shared_ptr<TFunction>(new Polinoms(input));
    else if (func == "exp")
        return std::shared_ptr<TFunction>(new Exp(input));
    else
        throw std::logic_error("Wrong Function type");
}

std::shared_ptr<TFunction> FuncFactory::Create(std::string func) {
    if (func == "ident")
        return std::shared_ptr<TFunction>(new Polinoms());
    else
        throw std::logic_error("It is not ident function");

}
