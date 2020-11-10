//
// Created by voland on 10.11.2020.
//

#ifndef SIMULATED_ANNEALING_SOLUTION_H
#define SIMULATED_ANNEALING_SOLUTION_H

#include <iostream>
#include <time.h>
#include <variant>
#include "../Temperature/Temperature.h"
#include "../Mutation/Mutation.h"
#include "../Structures.h"


template <class T, class S, class M>
class Simulating {
private:
    BaseSolution *best;
    BaseSolution *solution;
    BaseMutation *result; //NeedFix
    size_t it = 0;
    Temperature *temp_module; //NeedFix
public:
    Simulating(std::vector <int> data, int cores, int start_temp) {
        result = new M(data); //NeedFix
        solution = result->InitSolution(cores);
        best = solution;
        temp_module = new T(start_temp); //NeedFix

    }

    S* Solution_find() {

        while (it < 100){
            double new_temp = temp_module->getTemp();
            std::cout << new_temp << "-----" << it <<std::endl;

            for (size_t i = 0; i < 10; i++) {
                S tst = result->GetSolution(*dynamic_cast<S*>(solution));
                size_t diff = solution->CriterionGet() - tst.CriterionGet();
                if (diff) {
                    solution = tst.GetCopy();
                    if (solution->CriterionGet() <= best->CriterionGet()) {
                        it=0;
                        delete(best);
                        best = solution;
                    }
                } else {
                    float x = (rand() % 100) / (100 * 1.0);

                    if (exp(-diff / new_temp) > x) {
                        delete(solution);
                        solution = tst.GetCopy();

                    }

                }
            }
            it++;
        }
        delete(temp_module);
        delete(solution);
        return dynamic_cast<S*>(best);

    }


};

#endif //SIMULATED_ANNEALING_SOLUTION_H
