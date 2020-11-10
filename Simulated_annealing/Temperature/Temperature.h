//
// Created by voland on 10.11.2020.
//

#ifndef SIMULATED_ANNEALING_TEMPERATURE_H
#define SIMULATED_ANNEALING_TEMPERATURE_H

//
// Created by voland on 09.11.2020.
//
#include <math.h>

class Temperature
{
protected:
    double temp;
    int it = 0;
public:
    Temperature(double temperature=0) : temp(temperature) {}

    virtual double getTemp() = 0;

    virtual ~Temperature() = default;
};

class Boltzman: public Temperature
{
public:
    Boltzman(double temp=0): Temperature(temp) {}

    virtual double getTemp();
};

class Cauchy: public Temperature
{
public:
    Cauchy(double temp=0): Temperature(temp) {}

    virtual double getTemp();
};

class Basic: public Temperature
{
public:
    Basic(double temp=0): Temperature(temp) {}

    virtual double getTemp();
};

#endif //SIMULATED_ANNEALING_TEMPERATURE_H
