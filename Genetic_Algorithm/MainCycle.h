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
    float mut_probability;
    int exp_numb;
    int launch_numb;

public:
    MainCycle();
    void Start(float mut, int numb, int launch);
    void WriteInFile(space &best, bool last);
    void PrintResult(space &best);
    void Clear();
};




#endif //GENETIC_ALGORITHM_MAINCYCLE_H
