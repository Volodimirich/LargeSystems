//
// Created by voland on 11.11.2020.
//

#ifndef SIMULATED_ANNEALING_SIMULATING_PARRALEL_H
#define SIMULATED_ANNEALING_SIMULATING_PARRALEL_H
#include "Simulating.h"
#include <thread>
#include <mutex>


template <class T, class S, class M>
class ParallelSimulating{
private:
    int num_procs;
    int temp;
    int cores_amount;
    std::vector <int> inform;
    std::vector <BaseSolution*> worktask;
    std::mutex writelock;

public:
    ParallelSimulating(int procs, std::vector <int> data, int cores, int start_temp): num_procs(procs),
        temp(start_temp), cores_amount(cores), inform(data) {}

    void InitWorkTask(){
        Simulating<T,S,M> sim(inform, cores_amount, temp);
        writelock.lock();
        worktask.emplace_back(sim.Solution_find()->GetCopy());
        writelock.unlock();
    };

    BaseSolution* ParralelSolution() {
        std::vector<std::thread> thread_vec(num_procs);
        for (size_t i=0; i<num_procs; i++)
            thread_vec[i] = std::thread(&ParallelSimulating::InitWorkTask, this);

        for (auto &th: thread_vec)
            if (th.joinable())
                th.join();

        return GetBestSolution();

    }



    BaseSolution* GetBestSolution() {
        std::vector <int> allcrit;
        BaseSolution* tst;
        for (auto &it: worktask)
            allcrit.emplace_back(it->CriterionGet());

        int max = *std::max_element(allcrit.begin(), allcrit.end());
        for (auto it: worktask) {
            if (it->CriterionGet() == max)
                tst = it->GetCopy();
            delete(it);
        }
        return tst;
    }

};


#endif //SIMULATED_ANNEALING_SIMULATING_PARRALEL_H
