//
// Created by voland on 10.11.2020.
//

#ifndef SIMULATED_ANNEALING_MUTATION_H
#define SIMULATED_ANNEALING_MUTATION_H

#include "../Structures.h"
#include <random>



class BaseMutation {
protected:
    std::vector <int> input;
public:
    BaseMutation(std::vector <int> input_data = {}) {
        input = input_data;
    }

    virtual Solution *InitSolution(int cores) = 0;

    virtual Solution GetSolution(Solution solution) = 0;

    virtual ~BaseMutation() = default;
};




class Mutation : public BaseMutation {

public:
    Mutation(std::vector <int> input_data = {}) : BaseMutation(input_data) {}

    virtual Solution GetSolution(Solution solution);

    virtual Solution* InitSolution(int cores);
};

#endif //SIMULATED_ANNEALING_MUTATION_H
