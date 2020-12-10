//
// Created by voland on 08.12.2020.
//

#ifndef FACT_LIB_H
#define FACT_LIB_H

#include <memory>
#include <iostream>
#include <cmath>
#include <string>
#include <initializer_list>
#include <stdexcept>
#include "Functions.h"


class FuncFactory {
public:
    std::shared_ptr<TFunction> Create(std::string func, const std::initializer_list<double> &input);
    std::shared_ptr<TFunction> Create(std::string func, double input);
    std::shared_ptr<TFunction> Create(std::string func);
};

#endif
