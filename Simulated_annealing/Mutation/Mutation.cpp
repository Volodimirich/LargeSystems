#include "../Structures.h"
#include "Mutation.h"
#include <random>




Solution* Mutation::InitSolution(int cores) {
    Solution *new_solution = new Solution(cores);

    for (auto &it: input)
        new_solution->Insertation(0, it);


    return new_solution;
}

BaseSolution* Mutation::GetSolution(BaseSolution *solution) {
    BaseSolution* new_sol = solution->GetCopy();
    int pos;
    int new_pos;
    do {
        pos = rand() % new_sol->CoresAmount();
    } while (new_sol->EmptyLine(pos));
    int command = new_sol->RandomPositions(pos);
    do {
        new_pos = rand() % new_sol->CoresAmount();
    } while (pos == new_pos);

    new_sol->Insertation(new_pos, command);

    return new_sol;
}