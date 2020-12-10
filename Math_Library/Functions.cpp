//
// Created by voland on 09.12.2020.
//

#include "Functions.h"
#include <memory>
#include <iostream>
#include <cmath>
#include <string>
#include <initializer_list>
#include <stdexcept>


//Power TFunction module
PowerFunc::PowerFunc (double input) {
    var = input;
}

const std::string PowerFunc::ToString() {
    return std::string("x^") + std::to_string(var);
}

double PowerFunc::Deriv(double point) {
    return var * pow(point, var - 1);
}

double PowerFunc::operator()(double point) {
    return pow(point, var);
}


//Exponent TFunction module
Exp::Exp (double input) {
    var = input;
}

const std::string Exp::ToString() {
    return std::to_string(var) + std::string("^x");
}

double Exp::Deriv(double point) {
    return  pow(var, point) * log(var);
}

double Exp::operator()(double point) {
    return pow(var, point);
}


//Polinon TFunction Module
Polinoms::Polinoms (double numb) {
    coefficients.emplace_back(numb);
}

Polinoms::Polinoms (std::initializer_list<double> numbers) {
        for (auto& it: numbers) {
            coefficients.emplace_back(it);
        }
    }

Polinoms::Polinoms () {
    coefficients.emplace_back(0);
    coefficients.emplace_back(1);
}

const std::string Polinoms::ToString() {
    std::string result = coefficients[0] == 0 ? std::string("") : std::to_string(coefficients[0]);
    for (size_t i = 1; i < coefficients.size(); i++)
        if (coefficients[i] != 0)
            if (result.empty())
                result = std::to_string(coefficients[i]) + + "*x^" + std::to_string(i);
            else
                result += " + " + std::to_string(coefficients[i]) + "*x^" + std::to_string(i);

    return result;
}

double Polinoms::Deriv(double point) {
    double result = 0;

    for (size_t i = 1; i < coefficients.size(); i++)
        result += coefficients[i] * pow(point, i-1) * i;

    return result;
}

double Polinoms::operator()(double point) {
    double result = 0;

    for (size_t i = 0; i < coefficients.size(); i++)
        result += coefficients[i] * pow(point, i);

    return result;
}


// Composite TFunction module
CompFunction::CompFunction(std::shared_ptr<TFunction> func1, std::shared_ptr<TFunction> func2, std::string oper){
    function1 = func1;
    function2 = func2;
    operator_name = oper;
}
const std::string  CompFunction::ToString() {
    return function1->ToString() + operator_name + function2->ToString();
}

double  CompFunction::Deriv(double point) {
    if (operator_name == "+") {
        return function1->Deriv(point) + function2->Deriv(point);
    }
    else if (operator_name == "-")
    {
        return function1->Deriv(point) - function2->Deriv(point);
    }
    else if (operator_name == "*")
    {
        return function1->Deriv(point)*(*function2)(point) + (*function1)(point)*function2->Deriv(point);
    }
    else if (operator_name == "/")
    {
        return (function1->Deriv(point) * (*function2)(point) -
                (*function1)(point)*function2->Deriv(point)) / pow((*function2)(point), 2);
    }
    else {
        throw std::logic_error("Wrong operation");
    }
}

double  CompFunction::operator()(double point) {
    if (operator_name == "+") {
        return (*function1)(point) + (*function2)(point);
    }
    else if (operator_name == "-")
    {
        return (*function1)(point)- (*function2)(point);
    }
    else if (operator_name == "*")
    {
        return (*function1)(point) * (*function2)(point);
    }
    else if (operator_name == "/")
    {
        return  (*function1)(point) / (*function2)(point);
    }
    else {
        throw std::logic_error("Wrong operation");
    }
}



std::shared_ptr<TFunction> operator+(std::shared_ptr<TFunction> func1, std::shared_ptr<TFunction> func2) {
    return std::shared_ptr<TFunction> (new CompFunction(func1, func2, "+"));
}

std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction> &func1, std::shared_ptr<TFunction> &func2) {
    return std::shared_ptr<TFunction> (new CompFunction(func1, func2, "-"));
}

std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction> &func1, std::shared_ptr<TFunction> &func2) {
    return std::shared_ptr<TFunction> (new CompFunction(func1, func2, "*"));
}

std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction> &func1, std::shared_ptr<TFunction> &func2) {
    return std::shared_ptr<TFunction> (new CompFunction(func1, func2, "/"));
}

double gradient_descent(TFunction *func, size_t itt, double eps, double coef) {
    double solution = 1;
    for (size_t i = 0; i < itt; i++) {
        solution = solution - coef * func->Deriv(solution);
        if (fabs((*func)(solution)) < eps)
            return solution;
    }
    std::cout << "Can't find solution" << std::endl;
    return solution;
}