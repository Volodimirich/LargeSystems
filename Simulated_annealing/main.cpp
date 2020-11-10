//
// Created by voland on 09.11.2020.
//
#include <iostream>
#include <time.h>
#include "Temperature/Temperature.h"
#include "Mutation/Mutation.h"
#include "Structures.h"

int main(){
    data a1 = {'A',7};
    data a2 = {'A',7};
    data a3 = {'A',7};
    data a4 = {'A',7};
    data a5 = {'A',7};
    data a6 = {'A',7};
    data a7 = {'A',7};
    data a8 = {'A',7};
    data a9 = {'A',7};
    data a10 = {'A',7};
    data a11 = {'A',7};
    data a12 = {'A',7};
    data a13 = {'A',7};
    data a14 = {'A',7};
    data a15 = {'A',7};
    data a16 = {'A',7};
    data a17 = {'A',7};
    data a18 = {'A',7};
    srand(time(NULL));

    std::vector <data> test = {a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18};
    size_t it = 0;
    Mutation result(test);
    Solution solution = result.InitSolution(2);
    Boltzman temp_module(100);
    Solution best = solution;

    while (it < 100){
        double new_temp = temp_module.getTemp();
        std::cout << new_temp << "-----" << it <<std::endl;

        for (size_t i=0; i<10; i++) {
            Solution tst = result.GetSolution(solution);
            size_t diff = solution.CriterionGet() - tst.CriterionGet();
            if (diff) {
                solution = tst;
                if (solution.CriterionGet() <= best.CriterionGet()) {
                    it=0;
                    best = solution;
                }
            } else {
                float x = (rand() % 100) / (100 * 1.0);

                if (exp(-diff / new_temp) > x) {
                    solution = tst;
                }

            }
        }
        it++;
    }

    std::cout << "!";
    best.PrintResults();

    return 0;
}