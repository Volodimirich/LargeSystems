//
// Created by voland on 15.12.2020.
//

#include "MainCycle.h"
#include "vector"





MainCycle::MainCycle() {
    space gen;
    std::vector<int> line;

    for (size_t pop = 0; pop<POPULATION_SIZE; pop++){
        for (size_t i=0; i<FIELD; i++) {
            for (size_t j = 0; j < FIELD; j++) {
                line.emplace_back(rand() % 2);
            }
            gen.emplace_back(line);
            line.clear();
        }
        population.emplace_back(gen);
        gen.clear();
    }
}

std::vector<space> MainCycle::Start() {
    Estimation estim;
    Selection select;
    Crossing cross;
    Mutation mutate;
    std::pair <space, int> best = {{}, 0};
    int pos;
    size_t best_itt = 0;
    while (best_itt < 20) {
        pos = -1;
        std::vector<std::pair<space, int>> population_estimition = estim.GetEstimation(population);

        for (size_t i = 0; i < population_estimition.size(); i++) {
            if (population_estimition[i].second > best.second) {
                best.second = population_estimition[i].second;
                pos = i;
            }
        }

        if (pos != -1) {
            best.first = population_estimition[pos].first;
            best_itt = 0;
        } else {
            best_itt++;
        }

        std::vector<space> new_gen = select.GetSelect(population_estimition, 8, POPULATION_SIZE / 2);
        cross.GetCrossing(new_gen);
        mutate.GetMutation(new_gen);
        population = new_gen;
    }

    return population;
}



