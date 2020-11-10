//
// Created by voland on 09.11.2020.
//

#ifndef SIMULATED_ANNEALING_STRUCTURES_H
#define SIMULATED_ANNEALING_STRUCTURES_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>


class SingleLoad {
private:
    std::vector <int> load;
public:
    SingleLoad() = default;

    SingleLoad(std::vector <int> data) {
        load.clear();
        load = data;
    }

    std::vector <int> GetVec() {
        return load;
    }

    int GetLen() {
        int current = 0;
        for (auto & it : load)
            current += it;
        return current;
    }

    void Clear() {
        load.clear();
    }

    void WorkloadAdd(size_t size) {
        load.emplace_back(size);
    }

    int WorkloadRandomDelete() {
        int position = rand() % load.size();
        int command = load[position];
        load.erase(load.begin() + position);
        return command;
    }

    bool Empty() {
        return load.empty();
    }
};

class BaseSolution{
protected:
    std::unordered_map <int, SingleLoad> global_loading;
    size_t amount;
public:
    BaseSolution(int cores = 0) {
        amount=cores;
        for (size_t i=0; i<amount; i++)
            global_loading[i] = SingleLoad();
    }

    BaseSolution(int cores, std::unordered_map<int, SingleLoad> loading) {
        amount = cores;
        for (size_t i=0; i<amount; i++)
            global_loading[i] = SingleLoad(loading[i].GetVec());
    }

    virtual void Insertation(int position, int size) = 0;


    virtual int CriterionGet() = 0;

    virtual int CoresAmount() = 0;

    virtual int RandomPositions(int position) = 0;

    virtual bool EmptyLine(int position) = 0;

    virtual void PrintResults() = 0;


};


class Solution: public BaseSolution{
public:
    Solution(int cores = 0) : BaseSolution(cores) {};

    Solution(int cores, std::unordered_map<int, SingleLoad> loading) : BaseSolution(cores, loading) {};


    virtual void Insertation(int position, int size) {
        global_loading[position].WorkloadAdd(size);
    }

    int CriterionGet() {
        std::vector <int> loads_len;
        for (size_t i=0;  i<amount; i++)
            loads_len.emplace_back(global_loading[i].GetLen());
        return *max_element(loads_len.begin(), loads_len.end()) - *min_element(loads_len.begin(), loads_len.end());
    }

    int CoresAmount() {
        return amount;
    }

    int RandomPositions(int position) {
        return global_loading[position].WorkloadRandomDelete();

    }

    bool EmptyLine(int position) {
        return global_loading[position].Empty();
    }

    void PrintResults() {
        for (size_t i=0; i<amount; i++) {
            std::cout << i << "___" << global_loading[i].GetLen() << std::endl;
        }
    }

    Solution* GetCopy() {
        Solution *copy = new Solution(amount, global_loading);
        return copy;
    }
};

#endif //SIMULATED_ANNEALING_STRUCTURES_H