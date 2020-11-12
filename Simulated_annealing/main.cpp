//
// Created by voland on 09.11.2020.
//

#include "Temperature/Temperature.h"
#include "Mutation/Mutation.h"
#include "Structures.h"
#include "Simulating/Simulating.h"
#include "Simulating/Simulating_parralel.h"
#include "Generator/Generator_csv.h"


int main() {
    bool parallel = 0;
    size_t mode = 0;
    int proc_am, work_am, min, max;
    proc_am = 11;
    work_am = 13000;
    min = 11;
    max = 110;

//    std::cout << "Please select a working mode (0 - serial, 1 - parallel)" << std::endl;
//    std::cin >> parallel;
//    std::cout << "Choose temperature mode (0 - Boltzman, 1 - Cauchy, else Basic)" << std::endl;
//    std::cin >> mode;
//    std::cout << "Print processors amount"<< std::endl;
//    std::cin >> proc_am;
//    std::cout << "Choose work amounts" << std::endl;
//    std::cin >> work_am;
//    std::cout << "Print mininmum and maximum len(use enter)" << std::endl;
//    std::cin >> min >> max;
//    std::cout << "New?" << std::endl;
//    bool place;
//    std::cin>> place;
//    if (place)
//        GenerateCSV(proc_am, work_am, std::make_pair(min,max));
    InputDate date = ReadCSV();
    unsigned int start_time = clock();
    Simulating<Basic, Solution, Mutation> sim(date.data, date.proc_num, 100);
    sim.Solution_find()->PrintResults();
    unsigned int end_time = clock();
//

//    ParallelSimulating<Boltzman,Solution,Mutation> start(4, date.data,  date.proc_num, 100);
//    start.ParralelSolution()->PrintResults();


    std::cout << "Program worktime - " << double (end_time - start_time) / CLOCKS_PER_SEC << std::endl;
    return 0;
}
