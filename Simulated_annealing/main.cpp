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
    bool parallel = 0;
    size_t mode = 0;
    int proc_am, work_am, min, max;
    proc_am = 110;
    work_am = 1100;
    min = 1;
    max = 10;

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

    auto a = argv[1];

//    if (std::string(argv[1]) == "1") {
//        std::cout << argv[1];
    GenerateCSV(proc_am, work_am, std::make_pair(min, max));
//    }
    InputDate date = ReadCSV();
    std::cout << min << "___" << max << std::endl;
    std::cout << "Solo launch" << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();
//    if (std::string(argv[2]) == "0") {
    Simulating<Cauchy, Solution, Mutation> sim(date.data, date.proc_num, 100);
    sim.Solution_find()->PrintResults();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> worktime = end_time - start_time;
    std::cout << "Program worktime - " << worktime.count()/1000 <<"s" << std::endl;

//    }
//    else if (std::string(argv[2]) == "1") {
//        Simulating<Cauchy, Solution, Mutation> sim(date.data, date.proc_num, 100);
//        sim.Solution_find()->PrintResults();
//    }
//    else {
//        Simulating<Basic, Solution, Mutation> sim(date.data, date.proc_num, 100);
//        sim.Solution_find()->PrintResults();
//    }

//
    std::cout << "Parallel launch 1" << std::endl;
    auto start_time1 = std::chrono::high_resolution_clock::now();
    ParallelSimulating<Cauchy,Solution,Mutation> start(3, date.data,  date.proc_num, 100);
    start.ParralelSolution()->PrintResults();
    auto end_time1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> worktime1 = end_time1 - start_time1;
    std::cout << "Program worktime - " << worktime1.count()/1000 <<"s" << std::endl;

    std::cout << "Parallel launch2" << std::endl;
    auto start_time2 = std::chrono::high_resolution_clock::now();
    ParallelSimulating<Cauchy,Solution,Mutation> start2(3, date.data,  date.proc_num, 100);
    start2.ParralelSolution()->PrintResults();
    auto end_time2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> worktime2 = end_time2 - start_time2;
    std::cout << "Program worktime - " << worktime2.count()/1000 <<"s" << std::endl;

    std::cout << "Parallel launch3" << std::endl;
    auto start_time3 = std::chrono::high_resolution_clock::now();
    ParallelSimulating<Cauchy,Solution,Mutation> start3(3, date.data,  date.proc_num, 100);
    start3.ParralelSolution()->PrintResults();
    auto end_time3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> worktime3 = end_time3 - start_time3;
    std::cout << "Program worktime - " << worktime3.count()/1000 <<"s" << std::endl;


    return 0;
}
