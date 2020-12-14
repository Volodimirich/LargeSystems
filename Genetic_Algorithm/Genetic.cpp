//
// Created by voland on 14.12.2020.
//
#define FIELD 10
#define GENSIZE 3
#define MUTATION_AMOUNT 100
#define MUTATION_PROBABILITY 0.6
#include "Genetic.h"
#include "random"
#include "set"

size_t Estimation::NeighborReaction(space &gen, std::pair<size_t, size_t> pos){
    size_t reaction = 0;
    int pos_x, pos_y;
    for (int i=-1; i<=1; i++)
        for (int j=-1; j<=1; j++) {
            pos_x = pos.first + i;
            pos_y = pos.second + i;

            if (pos_x == 0 and pos_y == 0)
                break;

            if (pos.first + i >= 0 and pos.second + i >= 0 and pos.first + i <= FIELD and pos.second + i <= FIELD) {
                if (gen[pos_x][pos_y])
                    reaction++;
            }
        }
    if (reaction<=1 or reaction>=4)
        return 0;
    else if (reaction == 2)
        return 1;
    else
        return 2;
}

space Estimation::LifeStart(space &gen, size_t step_amount) {
    space new_gen = gen;

    for (size_t itt=0; itt<step_amount; itt++) {
        for (size_t x = 0; x <= FIELD; x++)
            for (size_t y = 0; y <= FIELD; y++) {
                std::pair<size_t, size_t> pos = {x, y};
                if ((new_gen[x][y] and NeighborReaction(new_gen, pos)) or (NeighborReaction(new_gen, pos) == 2))
                    new_gen[x][y] = 1;
                else
                    new_gen[x][y] = 0;
            }
    }
    return new_gen;
}

std::vector <std::pair<space,int>> Estimation::GetEsimation(std::vector <space> &gen) {
    std::vector <space> new_gen = gen;
    std::vector <std::pair<space,int>> result;
    int cur;

    for (size_t i=0; i<GENSIZE; i++){
        LifeStart(new_gen[i], MUTATION_AMOUNT - 1);
    }

    std::vector <space> last_gen = new_gen;
    for (size_t i=0; i<GENSIZE; i++){
        LifeStart(new_gen[i], 1);
    }


    for (size_t num=0; num<GENSIZE; num++){
        cur = 0;
        for (size_t i = 0; i < last_gen[num].size(); i++) {
            for (size_t j = 0; j < last_gen[num][0].size(); j++)
                if (last_gen[num][i][j])
                    cur++;
        }
        result.emplace_back(std::make_pair(new_gen[num], last_gen[num] == new_gen[num] ? cur - FIELD*FIELD : cur));
    }

    return result;
}

std::vector<space> Selection::GetSelect(std::vector <std::pair<space,int>> solution, size_t tournament_size,
                                        size_t amount) {

    std::set <int> players;
    std::vector <space> result;
    size_t player_num;
    int best;

    for (size_t tour=0; tour < amount; tour++) {
        best = -1;
        players.clear();

        while (players.size() != tournament_size) {
            player_num = rand() % solution.size();
            players.emplace(player_num);
        }

        for (auto &player: players) {
            if (best == -1) {
                best = player;
            } else {
                best = solution[best].second > solution[player].second ? best : player;
            }

            result.emplace_back(solution[best].first);
        }
    }
    return result;
}


void Crossing::GetCrossing(std::vector <space> &solution) {
    size_t first, second, pos;
    space new_sol;

    while (solution.size() < GENSIZE) {
        first = rand() % solution.size();
        do {
            second = rand() % solution.size();
        } while (first == second);

        pos = rand() % solution[first].size();
        std::copy(solution[first].begin(), solution[first].begin() + pos, std::back_inserter(new_sol));
        std::copy(solution[second].begin() + pos, solution[first].end(), std::back_inserter(new_sol));

        solution.emplace_back(new_sol);
        new_sol.clear();
    }

}

void Mutation::GetMutation(std::vector<space> &solution) {
    float mut;

    for (auto &solution_solo : solution) {
        for (size_t x = 0; x <= FIELD; x++)
            for (size_t y = 0; y <= FIELD; y++) {
                mut = (rand() % 100) / (100 * 1.0);
                if (mut > MUTATION_PROBABILITY)
                    solution_solo[x][y] = !solution_solo[x][y];
            }
    }
}
