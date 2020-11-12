#include <iostream>
#include "Generator/Generator_csv.h"

int main() {
    bool parallel = 0;
    int mode = 0;
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

    GenerateCSV(proc_am, work_am, std::make_pair(min,max));
};