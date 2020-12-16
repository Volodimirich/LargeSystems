//
// Created by voland on 15.12.2020.
//
#include "Genetic.h"
#ifndef GENETIC_ALGORITHM_MAINCYCLE_H
#define GENETIC_ALGORITHM_MAINCYCLE_H


class MainCycle {
private:
    std::vector<space> population;
    std::unique_ptr<AbstEstimation> estim;
    std::unique_ptr<AbstSelection> select;
    std::unique_ptr<AbstCrossing> cross;
    std::unique_ptr<AbstMutation> mutate;
public:
    MainCycle();
    std::vector<space> Start();
    void PrintResult(space best);
    void Clear();
};




#endif //GENETIC_ALGORITHM_MAINCYCLE_H
