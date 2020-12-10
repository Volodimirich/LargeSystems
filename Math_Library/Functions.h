//
// Created by voland on 09.12.2020.
//


#ifndef FUNC_LIB_H
#define FUNC_LIB_H


#include <memory>
#include <iostream>
#include <cmath>
#include <string>
#include <initializer_list>
#include <stdexcept>
#include <vector>

class TFunction {
public:
    virtual const std::string ToString () = 0;
    virtual double Deriv(double Point) = 0;
    virtual double operator()(double Point) = 0;
};

class PowerFunc: public TFunction {
private:
    double var;
public:
    PowerFunc (double input);
    const std::string ToString();
    double Deriv(double point);
    double operator()(double point);
};

class Exp: public TFunction {
private:
    double var;
public:
    Exp (double input);
    const std::string ToString();
    double Deriv(double point);
    double operator()(double point);
};

class Polinoms: public TFunction {
private:
    std::vector <double> coefficients;
public:
    Polinoms (double numb);
    Polinoms (std::initializer_list<double> numbers);
    Polinoms ();
    const std::string ToString();
    double Deriv(double point) ;
    double operator()(double point);
};

class CompFunction : public TFunction{
private:
    std::shared_ptr<TFunction> function1;
    std::shared_ptr<TFunction> function2;
    std::string operator_name;

public:
    CompFunction(std::shared_ptr<TFunction> func1, std::shared_ptr<TFunction> func2, std::string oper);
    const std::string ToString();
    double Deriv(double point);
    double operator()(double point);

};

std::shared_ptr<TFunction> operator+(std::shared_ptr<TFunction> func1, std::shared_ptr<TFunction> func2);

std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction> &func1, std::shared_ptr<TFunction> &func2);

std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction> &func1, std::shared_ptr<TFunction> &func2);

std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction> &func1, std::shared_ptr<TFunction> &func2);

double gradient_descent(TFunction *func, size_t itt, double eps = 0.005, double coef = 1);

#endif