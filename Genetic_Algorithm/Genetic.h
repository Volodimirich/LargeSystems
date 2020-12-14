//
// Created by voland on 14.12.2020.
//
#include "iostream"
#include "vector"

#ifndef GENETIC_ALGORITHM_GENETIC_H
#define GENETIC_ALGORITHM_GENETIC_H

using space = std::vector <std::vector <int>>;

class AbstEstimation {
public:
    virtual std::vector<int> GetEstimation(std::vector <space> gen) = 0;
};

class AbstSelection {
public:
    virtual std::vector <space> GetSelect(std::vector <std::pair<space,int>> solution,
                                          size_t tournament_size, size_t amount) = 0;
};

class AbstCrossing {
public:
    virtual void GetCrossing(std::vector <space> &solution) = 0;
};

class AbstMutation {
public:
    virtual void GetMutation(std::vector <space> &solution) = 0;
};


class Estimation: public AbstEstimation
{
public:
    std::vector <std::pair<space,int>> GetEsimation(std::vector <space> &gen);
    space LifeStart(space &gen, size_t step_amount);
    size_t NeighborReaction(space &gen, std::pair<size_t, size_t> pos);
};

class Selection: public AbstSelection {
public:
    std::vector <space> GetSelect(std::vector <std::pair<space,int>> solution, size_t tournament_size, size_t amount);
};

class Crossing: public AbstCrossing {
public:
    void GetCrossing(std::vector <space> &solution);
};

class Mutation: public AbstMutation {
public:
    void GetMutation(std::vector <space> &solution);
};

#endif //GENETIC_ALGORITHM_GENETIC_H
