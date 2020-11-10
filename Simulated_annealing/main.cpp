//
// Created by voland on 09.11.2020.
//
#include <iostream>
#include <time.h>
#include "Temperature/Temperature.h"
#include "Mutation/Mutation.h"
#include "Structures.h"
#include "Simulating/Simulating.h"




int main() {
    Simulating<Boltzman, Solution, Mutation> sim({6, 3, 3, 3, 3, 3, 2, 1}, 4, 100);
    sim.Solution_find();
}
//
//int main(){
//
//
//    std::vector <int> test = {6, 3, 3, 3, 3, 3, 2, 1};
//    size_t it = 0;
//    Mutation result(test);
//    Solution solution = result.InitSolution(4);
//    Boltzman temp_module(100);
//    Solution best = solution;
//
//    while (it < 100){
//        double new_temp = temp_module.getTemp();
//        std::cout << new_temp << "-----" << it <<std::endl;
//
//        for (size_t i = 0; i < 10; i++) {
//            Solution tst = result.GetSolution(solution);
//            size_t diff = solution.CriterionGet() - tst.CriterionGet();
//            if (diff) {
//                solution = tst;
//                if (solution.CriterionGet() <= best.CriterionGet()) {
//                    it=0;
//                    best = solution;
//                }
//            } else {
//                float x = (rand() % 100) / (100 * 1.0);
//
//                if (exp(-diff / new_temp) > x) {
//                    solution = tst;
//                }
//
//            }
//        }
//        it++;
//    }
//
//    best.PrintResults();
//
//    return 0;
//}