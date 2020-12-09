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
    virtual const std::string ToString () = 0;
    virtual double Deriv(double Point) = 0;
    virtual double operator() (double Point) = 0;
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

    double operator() (double point) {
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

    double operator() (double point) {
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

    double operator() (double point) {
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
    Operation operator_name;
    std::unordered_map<Operation, std::string> operation_dict = {{ADD,"+"}, {DEL,"-"},
                                                                 {MUL,"*"}, {DIV, "/"}};
public:
    CompFunction(std::shared_ptr<TFunction> func1, std::shared_ptr<TFunction> func2, Operation oper){
        function1 = func1;
        function2 = func2;
        operator_name = oper;
    }
    const std::string ToString() {
        function1->ToString()


};

#endif //MATH_LIBRARY_FUNCTIONS_H
