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

    void InitWorkTask(BaseSolution* best){
        Simulating<T,S,M> sim(inform, cores_amount, temp, best);
        BaseSolution* sol = sim.Solution_find()->GetCopy();
        writelock.lock();
        worktask.emplace_back(sol);
        writelock.unlock();
    };

    BaseSolution* ParralelSolution() {
        std::vector<std::thread> thread_vec(num_procs);
        BaseSolution* best = nullptr;
        int it=0;

        while (it<10) {
            for (size_t i = 0; i < num_procs; i++)
                thread_vec[i] = std::thread(&ParallelSimulating::InitWorkTask, this, best);

            for (auto &th: thread_vec)
                if (th.joinable())
                    th.join();
            if (best) {
                BaseSolution* new_solution = this->GetBestSolution();
                if (new_solution->CriterionGet() < best->CriterionGet()) {
                    delete (best);
                    best = new_solution->GetCopy();
                    delete (new_solution);
                    it = 0;
                } else {
                    delete(new_solution);
                    it++;
                }
            } else {
                best = this->GetBestSolution()->GetCopy();
                it=1;
            }
            thread_vec.clear();
            thread_vec.resize(num_procs);
            worktask.clear();
        }
        return best;

    }



    BaseSolution* GetBestSolution() {
        std::vector <int> allcrit;
        BaseSolution* tst = nullptr;
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
