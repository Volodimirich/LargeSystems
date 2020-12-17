#include <iostream>
#include "Genetic.h"
#include "MainCycle.h"
#include "cmath"
#include <sstream>

int main(int argc, char *argv[]) {
    MainCycle m;
    float mut;
    srand(time(0));
    std::stringstream conv_1(argv[1]), conv_2(argv[2]);
    int numb, launch;
    conv_1 >> numb;
    conv_2 >> launch;
    mut = (1/pow(FIELD,2))*(pow(1.5,numb));
    std::cout <<mut;
    m.Start(mut, numb, launch);
    return 0;
}