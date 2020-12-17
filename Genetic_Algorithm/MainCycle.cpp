//
// Created by voland on 15.12.2020.
//

#include "MainCycle.h"
#include "vector"
#include <unistd.h>
#include <fstream>
#include "string"

void MainCycle::Clear() {
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void MainCycle::WriteInFile(space &best, bool last) {

    std::string filename = !last ? "series_" + std::to_string(exp_numb) + "_run_" + std::to_string(launch_numb) + ".txt" :
        "series_" + std::to_string(exp_numb) + "_run_" + std::to_string(launch_numb) + "_sol_after100.txt";
    std::ofstream file(filename.c_str());

    for (size_t i = 0; i < best.size(); i++) {
        for (size_t j = 0; j < best[i].size(); j++) {
            auto symb = best[i][j] == 1 ? "#" : ".";
            file << symb;
        }
        file << std::endl;
    }
    file.close();
}

void MainCycle::PrintResult(space &best) {
    WriteInFile(best, false);
    for (size_t it = 0; it<101; it++) {
//        for (size_t i = 0; i < best.size(); i++) {
//            for (size_t j = 0; j < best[i].size(); j++) {
//                auto symb = best[i][j] == 1 ? "#" : ".";
//                std::cout << symb;
//            }
//            std::cout << std::endl;
//        }
        estim->LifeStart(best, 1);
//        usleep(500000);
//        Clear();
    }
    WriteInFile(best, true);
}



MainCycle::MainCycle() {
    space gen;
    std::vector<int> line;
    estim = std::make_unique<Estimation> ();
    select = std::make_unique<Selection>();
    cross = std::make_unique<Crossing>();
    mutate = std::make_unique<Mutation>();

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

void MainCycle::Start(float mut, int numb, int launch) {

    std::pair <space, int> best = {{}, 0};
    int pos;
    size_t best_itt = 0;

    mut_probability = mut;
    exp_numb = numb;
    launch_numb = launch;


    while (best_itt < 20) {
        pos = -1;
        std::vector<std::pair<space, int>> population_estimition = estim->GetEstimation(population);

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

        std::vector<space> new_gen = select->GetSelect(population_estimition, 8, POPULATION_SIZE / 2);
        cross->GetCrossing(new_gen);
        mutate->GetMutation(new_gen, mut_probability);
        population = new_gen;
    }
    std::cout << "BEST" << best.second << std::endl;
    PrintResult(best.first);
}



