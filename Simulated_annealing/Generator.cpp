#include <iostream>
#include "Generator/Generator_csv.h"

int main() {
    int proc_am, work_am, min, max;
    std::cout << "Print processors amount"<< std::endl;
    std::cin >> proc_am;
    std::cout << "Choose work amounts" << std::endl;
    std::cin >> work_am;
    std::cout << "Print mininmum and maximum len(use enter)" << std::endl;
    std::cin >> min >> max;
    std::cout << "New?" << std::endl;
    GenerateCSV(proc_am, work_am, std::make_pair(min,max));
    return 0;
};