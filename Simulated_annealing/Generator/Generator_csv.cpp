//
// Created by voland on 11.11.2020.
//
#include <iostream>
#include <random>
#include <time.h>
#include <ctime>
#include <fstream>
#include <string>
#include "../Structures.h"


void GenerateCSV(int proc_num, int work_amount, std::pair<int, int> time_interval) {
    srand( time(0));
    std::ofstream input_date;
    input_date.open("input.csv");

    input_date << proc_num << ","<< work_amount << std::endl;
    for (size_t i=0; i< work_amount; i++)
        input_date << rand() % (time_interval.second - time_interval.first + 1) + time_interval.first << std::endl;

    input_date.close();
}

InputDate ReadCSV() {
    std::ifstream input_date;
    std::string line;
    size_t delimeter;
    InputDate Result;
    input_date.open("../input.csv");

    getline(input_date, line);

    delimeter = line.find(",");

    Result.proc_num = std::stoi(line.substr(0,delimeter+1));
    Result.work_amount = std::stoi(line.substr(delimeter+1, line.length() - delimeter - 1));


    while (getline(input_date, line)) {
        Result.data.emplace_back(std::stoi(line));
    }

    return Result;
}