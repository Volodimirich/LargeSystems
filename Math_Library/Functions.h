//
// Created by voland on 09.12.2020.
//
#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <initializer_list>
#include <stdexcept>

#ifndef MATH_LIBRARY_FUNCTIONS_H
#define MATH_LIBRARY_FUNCTIONS_H


enum Operation {
    ADD,
    DEL,
    MUL,
    DIV
};


class TFunction {
public:
    virtual const std::string ToString () = 0;
    virtual double Deriv(double Point) = 0;
    virtual double GetVal(double Point) = 0;
//    virtual ~TFunction() {}
};

class PowerFunc: public TFunction {
private:
    double var;
public:
    PowerFunc (double input) {
        var = input;
    }

    const std::string ToString() {
        return std::string("x^") + std::to_string(var);
    }

    double Deriv(double point) {
        return var * pow(point, var - 1);
    }

    double GetVal(double point) {
        return pow(point, var);
    }
};

class Exp: public TFunction {
private:
    double var;
public:
    Exp (double input) {
        var = input;
    }

    const std::string ToString() {
        return std::to_string(var) + std::string("^x");
    }

    double Deriv(double point) {
        return  pow(var, point) * log(var);
    }

    double GetVal(double point) {
        return pow(var, point);
    }
};

class Polinoms: public TFunction {
private:
    std::vector <double> coefficients;
public:
    Polinoms (double numb) {
        coefficients.emplace_back(numb);
    }

    Polinoms (std::initializer_list<double> numbers) {
        for (auto& it: numbers) {
            coefficients.emplace_back(it);
        }
    }

    Polinoms () {
        coefficients.emplace_back(0);
        coefficients.emplace_back(1);
    }

    const std::string ToString() {
        std::string result = std::to_string(coefficients[0]);
        for (int i = 1; i < coefficients.size(); i++)
            result += " + " + std::to_string(coefficients[i]);

        return result;
    }

    double Deriv(double point) {
        double result = 0;

        for (int i = 1; i < coefficients.size(); i++)
            result += coefficients[i] * pow(point, i-1) * i;

        return result;
    }

    double GetVal(double point) {
        double result = 0;

        for (int i = 0; i < coefficients.size(); i++)
            result += coefficients[i] * pow(point, i);

        return result;
    }
};

class CompFunction : public TFunction{
private:
    std::shared_ptr<TFunction> function1;
    std::shared_ptr<TFunction> function2;
    std::string operator_name;

public:
    CompFunction(std::shared_ptr<TFunction> func1, std::shared_ptr<TFunction> func2, std::string oper){
        function1 = func1;
        function2 = func2;
        operator_name = oper;
    }
    const std::string ToString() {
        return function1->ToString() + operator_name + function2->ToString();
    }

    double Deriv(double point) {
        if (operator_name == "+") {
            return function1->Deriv(point) + function2->Deriv(point);
        }
        else if (operator_name == "-")
        {
            return function1->Deriv(point) - function2->Deriv(point);
        }
        else if (operator_name == "*")
        {
            return function1->Deriv(point)*function2->GetVal(point) + function1->GetVal(point)*function2->Deriv(point);
        }
        else if (operator_name == "/")
        {
            return (function1->Deriv(point)*function2->GetVal(point) -
                    function1->GetVal(point)*function2->Deriv(point)) / pow(function2->GetVal(point), 2);
        }
        else {
            throw std::logic_error("Wrong operation");
        }
    }

    double GetVal(double point) {
        double result = 0;
        if (operator_name == "+") {
            return function1->GetVal(point) + function2->GetVal(point);
        }
        else if (operator_name == "-")
        {
            return function1->GetVal(point) - function2->GetVal(point);
        }
        else if (operator_name == "*")
        {
            return function2->GetVal(point) * function1->GetVal(point);
        }
        else if (operator_name == "/")
        {
            return function1->Deriv(point) /  function2->GetVal(point);
        }
        else {
            throw std::logic_error("Wrong operation");
        }
};

#endif //MATH_LIBRARY_FUNCTIONS_H
