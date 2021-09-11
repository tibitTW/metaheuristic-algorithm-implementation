#include "config.h"
#include "tsp.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>

typedef vector<int> Chromo;
using namespace std;

namespace ga {

void InitialChromosome(Chromo &c) {
    c.clear();
    c = tsp::getRandomPath();
}

// TODO: 3 versions of crossover
// 1. partially mapped crossover
void PMX() {}
// 2. cycle crossover
void CX() {}
// 3. order crossover
void OX() {}
void Crossover(Chromo &c1, Chromo &c2) {}

void Mutation(Chromo &c) {
    int f1 = rand() % CITY_DIM, f2 = rand() % CITY_DIM;
    while (f1 == f2)
        f2 = rand() % CITY_DIM;

    int tmp = c[f1];
    c[f1] = c[f2];
    c[f2] = tmp;
}

// TODO: calculate
double Evluation(Chromo &c) {}

int GA() {
    srand(time(NULL));
    /* ========== Initialization ========== */
    vector<Chromo> P(POP);
    vector<double> fitness(POP);
    double best_fitness;

    for (int ci = 0; ci < POP; ci++)
        InitialChromosome(P.at(ci));

    /* ========== Iteration ========== */
    for (int ii = 0; ii < ITERATION; ii++) {

        /* ========== Evaluation ========== */

        /* ========== Selection ========== */

        /* ========== Crossover ========== */
        for (int ci = 0; ci < POP; ci += 2) {
            if ((double)rand() < C_RATE)
                Crossover(P.at(ci), P.at(ci + 1));
        }

        /* ========== Mutation ========== */
        for (int ci = 0; ci < POP; ci++) {
            if ((double)rand() < M_RATE)
                Mutation(P.at(ci));
        }

        /* ========== Determination ========== */
    }

    return 0;
}

} // namespace ga