#include "../Structures.h"
#include "Mutation.h"
#include <random>




Solution* Mutation::InitSolution(int cores) {
    Solution *new_solution = new Solution(cores);

    for (auto &it: input) {
        int pos = rand() % cores;
        new_solution->Insertation(pos, it);
    }

    return new_solution;
}

Solution Mutation::GetSolution(Solution solution) {
    int pos;
    do {
        pos = rand() % solution.CoresAmount();
    } while (solution.EmptyLine(pos));
    int command = solution.RandomPositions(pos);
    int new_pos = rand() % solution.CoresAmount();
    solution.Insertation(new_pos, command);

    return solution;
}