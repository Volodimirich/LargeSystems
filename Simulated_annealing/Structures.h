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


struct InputDate{
    int proc_num = 0;
    int work_amount = 0;
    std::vector <int> data = {};
};

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

    void Out() {
        for (auto& it: load) {
            std::cout << it << std::endl;
        }
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

    ~SingleLoad(){};
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

    virtual  BaseSolution* GetCopy() = 0;

    virtual ~BaseSolution() = default;

};


class Solution: public BaseSolution{
public:
    Solution(int cores = 0) : BaseSolution(cores) {};

    Solution(int cores, std::unordered_map<int, SingleLoad> loading) : BaseSolution(cores, loading) {};


    virtual void Insertation(int position, int size) {
        global_loading[position].WorkloadAdd(size);
    }

    virtual int CriterionGet() {
        std::vector <int> loads_len;

        for (size_t i=0;  i<amount; i++)
            loads_len.emplace_back(global_loading[i].GetLen());
        return *max_element(loads_len.begin(), loads_len.end()) - *min_element(loads_len.begin(), loads_len.end());
    }

    virtual int CoresAmount() {
        return amount;
    }

    virtual int RandomPositions(int position) {
        return global_loading[position].WorkloadRandomDelete();

    }



    virtual bool EmptyLine(int position) {
        return global_loading[position].Empty();
    }

    virtual void PrintResults() {
        std::cout << "Answer:" << std::endl;
        for (size_t i=0; i<amount; i++) {
            std::cout << "Proc №"<< i << " --- " << global_loading[i].GetLen() << std::endl;
//            global_loading[i].Out();
        }
        std::cout << "Deviation - " << this->CriterionGet() << std::endl;
    }

    virtual BaseSolution* GetCopy() {
        Solution *copy = new Solution(amount, global_loading);
        return copy;
    }
};

#endif //SIMULATED_ANNEALING_STRUCTURES_H
