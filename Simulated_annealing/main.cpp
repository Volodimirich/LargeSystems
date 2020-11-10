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
    Simulating<Boltzman, Solution, Mutation> sim({6, 3, 3}, 2, 100);
    sim.Solution_find()->PrintResults();
}
