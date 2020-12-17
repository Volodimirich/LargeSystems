//
// Created by voland on 14.12.2020.
//
#include "iostream"
#include "vector"
#include "memory"

#ifndef GENETIC_ALGORITHM_GENETIC_H
#define GENETIC_ALGORITHM_GENETIC_H
#define FIELD 5
#define POPULATION_SIZE 16
#define MUTATION_AMOUNT 100

using space = std::vector <std::vector <int>>;

class AbstEstimation {
public:
    virtual int LifeStart(space &gen, size_t step_amount, bool last = false) = 0;
    virtual  std::vector <std::pair<space,int>> GetEstimation(std::vector <space> &gen) = 0;
    AbstEstimation() = default;
    virtual ~AbstEstimation() = default;
};

class AbstSelection {
public:
    virtual std::vector <space> GetSelect(std::vector <std::pair<space,int>> solution,
                                          size_t tournament_size, size_t amount) = 0;
    AbstSelection() = default;
    virtual ~AbstSelection() = default;
};

class AbstCrossing {
public:
    virtual void GetCrossing(std::vector <space> &solution) = 0;
    AbstCrossing() = default;
    virtual ~AbstCrossing() = default;
};

class AbstMutation {
public:
    virtual void GetMutation(std::vector <space> &solution, float mut_probability) = 0;
    AbstMutation() = default;
    virtual ~AbstMutation() = default;
};


class Estimation: public AbstEstimation
{
private:
    size_t NeighborReaction(space &gen, std::pair<size_t, size_t> pos);
public:
    int LifeStart(space &gen, size_t step_amount, bool last = false);
    std::vector <std::pair<space,int>> GetEstimation(std::vector <space> &gen);
    Estimation() = default;
    ~Estimation() = default;
};

class Selection: public AbstSelection {
public:
    std::vector <space> GetSelect(std::vector <std::pair<space,int>> solution, size_t tournament_size, size_t amount);
    Selection() = default;
    ~Selection() = default;
};

class Crossing: public AbstCrossing {
public:
    void GetCrossing(std::vector <space> &solution);
    Crossing() = default;
    ~Crossing() = default;
};

class Mutation: public AbstMutation {
public:
    void GetMutation(std::vector <space> &solution, float mut_probability);
    Mutation() = default;
    ~Mutation() = default;
};

#endif //GENETIC_ALGORITHM_GENETIC_H
