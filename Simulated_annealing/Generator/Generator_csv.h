//
// Created by voland on 11.11.2020.
//

#ifndef SIMULATED_ANNEALING_GENERATOR_CSV_H
#define SIMULATED_ANNEALING_GENERATOR_CSV_H
#include <iostream>
#include "../Structures.h"

void GenerateCSV(int proc_num, int work_amount, std::pair<int, int> time_interval);
InputDate ReadCSV();

#endif //SIMULATED_ANNEALING_GENERATOR_CSV_H
