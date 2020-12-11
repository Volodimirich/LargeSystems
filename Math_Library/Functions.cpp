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
#include <sstream>
#include <iomanip>


//Power TFunction module
PowerFunc::PowerFunc (double input) {
    var = input;
}

const std::string PowerFunc::ToString() {
    std::stringstream output;
    int prec = var - int(var) < 0.0001 ? 0 : 3;
    output << std::fixed << std::setprecision(prec) << "x^" << var;
    return output.str();

//    return std::string("x^") + std::to_string(var);
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
    std::stringstream output;
    int prec = var - int(var) < 0.0001 ? 0 : 3;

    output << std::fixed << std::setprecision(prec) << var <<"^x";
    return output.str();

//    return std::to_string(var) + std::string("^x");
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

const std::string Polinoms::GetVal(int pos) {
    std::stringstream output;
    int prec = coefficients[pos] - int(coefficients[pos]) < 0.0001 ? 0 : 3;
    if (pos == 0) {
        output << std::fixed << std::setprecision(prec) << coefficients[0];
    } else if (pos == 1) {
        if (coefficients[1] == 1)
            output << "x";
        else
            output << std::fixed << std::setprecision(prec) << coefficients[pos] << "*x";
    } else
        if (coefficients[pos] == 1)
            output << std::fixed << std::setprecision(prec) << "x^" << pos;
        else
            output << std::fixed << std::setprecision(prec) << coefficients[pos] << "*x^" << pos;

    return output.str();
}

const std::string Polinoms::ToString() {
    std::stringstream output;
    bool started = false;
    if (coefficients[0] != 0) {
        output  << GetVal(0);
        started = true;
    }
    for (size_t i = 1; i < coefficients.size(); i++)
        if (coefficients[i] != 0) {
            if (started) {
                output << " + " << GetVal(i);
            } else {
                output << GetVal(i);
                started = true;
            }
        }
    return output.str();
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
    std::stringstream output;
    output << function1->ToString() << " " + operator_name + " " << function2->ToString();
    return output.str();
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

std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction> func1, std::shared_ptr<TFunction> func2) {
    return std::shared_ptr<TFunction> (new CompFunction(func1, func2, "-"));
}

std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction> func1, std::shared_ptr<TFunction> func2) {
    return std::shared_ptr<TFunction> (new CompFunction(func1, func2, "*"));
}

std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction> func1, std::shared_ptr<TFunction> func2) {
    return std::shared_ptr<TFunction> (new CompFunction(func1, func2, "/"));
}

double gradient_descent(std::shared_ptr<TFunction> func, size_t itt, double eps, double coef) {
    double solution = 1;
    int sign;
    for (size_t i = 0; i < itt; i++) {
        sign = (*func)(solution) > 0 ? -1 : 1;
        solution = solution + sign * coef * func->Deriv(solution);
        if (fabs((*func)(solution)) < eps)
            return solution;
    }
    std::cout << "Can't find solution" << std::endl;
    return solution;
}