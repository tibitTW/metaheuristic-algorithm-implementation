#include "onemax.h"

#include <functional>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <iostream>

namespace ga {

void crossover(onemax::solution &sol1, onemax::solution &sol2, int ci) {
    bool tmp;
    for (; ci < sol1.size(); ci++) {
        tmp = sol1.at(ci);
        sol1.at(ci) = sol2.at(ci);
        sol2.at(ci) = tmp;
    }
}
void mutation(onemax::solution &sol) {
    int ri = rand() % sol.size();
    sol.at(ri) = !sol.at(ri);
}

void ga(const int BIT_SIZE, const int ITERATION, const int POPULATION, const double CROSSOVER_P, const double MUTATION_P,
        vector<int> &result) {

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<unsigned> bit_slice(0, BIT_SIZE - 1);
    std::uniform_int_distribution<unsigned> distribution2(0, BIT_SIZE);
    std::uniform_int_distribution<unsigned> bool_dis(0, 1);
    std::uniform_real_distribution<double> distribution_f(0, 1);
    auto bool_dice = std::bind(bool_dis, generator);
    auto crossover_dice = std::bind(bit_slice, generator);
    auto double_dice = std::bind(distribution_f, generator);

    /* =============== INITIALIZATION =============== */
    vector<onemax::solution> P(POPULATION), P_next(POPULATION);
    for (int pi = 0; pi < POPULATION; pi++) {
        P.at(pi).resize(BIT_SIZE);
        onemax::init(P.at(pi));
        P_next.at(pi).resize(BIT_SIZE);
    }

    vector<int> Fitness(POPULATION);
    vector<double> wheel_selection_table(POPULATION);
    unsigned best_fitness = 0, f_sum;

    for (int ii = 0; ii < ITERATION; ii++) {

        /* =============== EVALUATION =============== */
        for (int pi = 0; pi < POPULATION; pi++) {
            Fitness.at(pi) = onemax::fitness(P.at(pi));
            best_fitness = best_fitness > Fitness.at(pi) ? best_fitness : Fitness.at(pi);
        }

        // output result of this iteration
        result.push_back(best_fitness);

        /* =============== SELECTION (wheel selection) =============== */

        f_sum = 0;
        for (int pi = 0; pi < POPULATION; pi++)
            f_sum += Fitness.at(pi);

        wheel_selection_table.at(0) = (double)Fitness.at(0) / f_sum;
        for (int pi = 1; pi < POPULATION; pi++) {
            wheel_selection_table.at(pi) = (double)Fitness.at(pi) / f_sum + wheel_selection_table.at(pi - 1);
        }

        for (int pi = 0; pi < POPULATION; pi++) {
            double select_flag = double_dice();

            for (int fi = 0; fi < POPULATION; fi++) {
                if (wheel_selection_table.at(fi) > select_flag) {
                    P_next.at(pi) = P.at(fi);
                    break;
                }
            }
        }

        /* =============== CROSSOVER =============== */
        for (int pi = 0; pi < POPULATION; pi += 2) {
            if (double_dice() < CROSSOVER_P)
                crossover(P_next.at(pi), P_next.at(pi + 1), crossover_dice());
        }

        /* =============== MUTATION =============== */
        for (int pi = 0; pi < POPULATION; pi++) {
            if (double_dice() < MUTATION_P)
                mutation(P_next.at(pi));
        }

        /* =============== DETERMINATION =============== */
        P = P_next;
    }

    /* =============== EVALUATION (for last population) =============== */
    for (int pi = 0; pi < POPULATION; pi++) {
        Fitness.at(pi) = onemax::fitness(P.at(pi));
        best_fitness = best_fitness > Fitness.at(pi) ? best_fitness : Fitness.at(pi);
    }

    // output result of this iteration
    result.push_back(best_fitness);
}
} // namespace ga
