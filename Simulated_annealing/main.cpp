//
// Created by voland on 09.11.2020.
//

#include "Temperature/Temperature.h"
#include "Mutation/Mutation.h"
#include "Structures.h"
#include "Simulating/Simulating.h"
#include "Simulating/Simulating_parralel.h"
#include "Generator/Generator_csv.h"
#include <chrono>


int main(int argc, char *argv[]) {
    srand( time(0));
    bool parallel;
    int th_am;
    int mode = 0;
    std::vector <int> inf = {1,2,4,6,8,10,12,14,16};
    std::cout << "Please select a working mode (0 - serial, 1 - parallel)" << std::endl;
    std::cin >> parallel;
    std::cout << "Choose temperature mode (0 - Boltzman, 1 - Cauchy, else Basic)" << std::endl;
    std::cin >> mode;
//    mode = 1;
//    parallel = true;


    InputDate date = ReadCSV();

    auto start_time = std::chrono::high_resolution_clock::now();
    if (not parallel) {
        if (mode == 0) {
            Simulating<Boltzman, Solution, Mutation> sim(date.data, date.proc_num, 100);
            sim.Solution_find()->PrintResults();
        } else if (mode == 1) {
            Simulating<Cauchy, Solution, Mutation> sim(date.data, date.proc_num, 100);
            sim.Solution_find()->PrintResults();
        } else {
            Simulating<Basic, Solution, Mutation> sim(date.data, date.proc_num, 100);
            sim.Solution_find()->PrintResults();
        }
    } else {
        std::cout << "Please, print amoint of threads:" << std::endl;
        std::cin >> th_am;
        if (mode == 0) {
            ParallelSimulating<Boltzman, Solution, Mutation> sim1(th_am, date.data, date.proc_num, 100);
            sim1.ParralelSolution()->PrintResults();
        } else if (mode == 1) {
            ParallelSimulating<Cauchy, Solution, Mutation> sim1(th_am, date.data, date.proc_num, 100);
            sim1.ParralelSolution()->PrintResults();
        } else {
            ParallelSimulating<Basic, Solution, Mutation> sim1(th_am, date.data, date.proc_num, 100);
            sim1.ParralelSolution()->PrintResults();
        }

//

    }
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> worktime = end_time - start_time;
        std::cout << "Program worktime - " << worktime.count() / 1000 << "s" << std::endl;

    return 0;
}
