#include "../Structures.h"
#include "Mutation.h"
#include <random>




Solution Mutation::InitSolution(int cores) {
    Solution new_solution(cores);

    for (auto &it: input) {
        int pos = rand() % cores;
        new_solution.Insertation(pos, it.first, it.second);
    }

    return new_solution;
}

Solution Mutation::GetSolution(Solution solution) {
    int pos;
    do {
        pos = rand() % solution.CoresAmount();
    } while (solution.EmptyLine(pos));
    data command = solution.RandomPositions(pos);
    int new_pos = rand() % solution.CoresAmount();
    solution.Insertation(new_pos, command.first, command.second);
    return solution;
}