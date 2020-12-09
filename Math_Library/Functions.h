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



class TFunction {
public:
    virtual const std::string ToString () = 0;
    virtual double Deriv(double Point) = 0;
    virtual double operator()(double Point) = 0;
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

    double operator()(double point) {
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

    double operator()(double point) {
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

    double operator()(double point) {
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

    double operator()(double point) {
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

    double gradient_descent(TFunction func, size_t itt, double eps = 0.005, double coef = 1) {
        double solution = 1;
        for (size_t i = 0; i < itt; i++) {
            solution = solution - coef * func.Deriv(solution);
            if (fabs(func(solution)) < eps)
                return solution;
        }
        std::cout << "Can't find solution" << std::endl;
        return solution;
    }

};


class FuncFactory {
public:
    std::shared_ptr<TFunction> Create(std::string func, const std::initializer_list<double> &input)
    {
        if (func == "polynomial")
            return std::shared_ptr<TFunction>(new Polinoms(input));
        else
            throw std::logic_error("Initializer list works only with polynomial function");
    }
    std::shared_ptr<TFunction> Create(std::string func, double input) {
        if (func == "power")
            return std::shared_ptr<TFunction>(new PowerFunc(input));
        else if (func == "const")
            return std::shared_ptr<TFunction>(new Polinoms(input));
        else if (func == "exp")
            return std::shared_ptr<TFunction>(new Exp(input));
        else
            throw std::logic_error("Wrong Function type");
    }
    std::shared_ptr<TFunction> Create(std::string Func) {
        if (Func == "ident")
            return std::shared_ptr<TFunction>(new Polinoms());
        else
            throw std::logic_error("It is not ident function");

    }
};


