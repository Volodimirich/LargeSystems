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

using data = std::pair<char, int>;

class SingleLoad{
private:
    std::vector <data> load;
public:
    SingleLoad() = default;

    int GetLen() {
//        return load.size();
        int current = 0;
        for (auto & it : load)
            current += it.second;
        return current;
    }

    void Clear() {
        load.clear();
    }

    void WorkloadAdd(char let, size_t size) {
        load.emplace_back(std::make_pair(let, size));
    }

    data WorkloadRandomDelete() {
        int position = rand() % load.size();
        data command = load[position];
        load.erase(load.begin() + position);
        return command;
    }

    bool Empty() {
        return load.empty();
    }
};

class Solution{
private:
    std::unordered_map <int, SingleLoad> global_loading;
    size_t amount;
public:
    Solution(int cores) {
        amount=cores;
        for (size_t i=0; i<amount; i++)
            global_loading[i] = SingleLoad();
    }

    void Insertation(int position, char let, size_t size) {
        global_loading[position].WorkloadAdd(let, size);
    }

    int CriterionGet() {
        std::vector <int> loads_len;
        for (size_t i=0;  i<amount; i++)
            loads_len.emplace_back(global_loading[i].GetLen());
        int max = *max_element(loads_len.begin(), loads_len.end());
        int min = *min_element(loads_len.begin(), loads_len.end());
        return max - min;
    }

    int CoresAmount() {
        return amount;
    }

    data RandomPositions(int position) {
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

};

#endif //SIMULATED_ANNEALING_STRUCTURES_H
