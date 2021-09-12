#include "config.h"
#include "tsp.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>

typedef vector<int> Chromo;
typedef vector<Chromo> Chromo_P;
using namespace std;

namespace ga {

void InitialChromosome(Chromo &c) {
    c.clear();
    c = tsp::getRandomPath();
}

// TODO: partially mapped crossover
void PMX(Chromo &c1, Chromo &c2) {}

// cycle crossover
void CX(Chromo &c1, Chromo &c2) {
    vector<int> mask(CITY_DIM, 1);
    int b = c1[0], e = c2[0];
    mask[0] = 0;
    while (b != e) {
        int ci = 0;
        while (e != c1[ci])
            ci++;
        mask[ci] = 0;
        e = c2[ci];
    }
}

// TODO: order crossover
void OX(Chromo &c1, Chromo &c2) {}

void Crossover(Chromo &c1, Chromo &c2) {
    switch (C_TYPE) {
    case 1:
        PMX(c1, c2);
        break;
    case 2:
        CX(c1, c2);
        break;
    case 3:
        OX(c1, c2);
        break;
    default:
        break;
    }
}

// TODO: roulette wheel selection
void RWS(Chromo_P &P_next, Chromo_P P, vector<double> fitness) {}
// TODO: tournament selection
void TS(Chromo_P &P_next, Chromo_P P, vector<double> fitness) {}

void Selection(Chromo_P &P_next, Chromo_P P, vector<double> fitness) {
    switch (S_TYPE) {
    case 1:
        RWS(P_next, P, fitness);
    case 2:
        TS(P_next, P, fitness);
    default:
        break;
    }
}

void Mutation(Chromo &c) {
    int f1 = rand() % CITY_DIM, f2 = rand() % CITY_DIM;
    while (f1 == f2)
        f2 = rand() % CITY_DIM;

    int tmp = c[f1];
    c[f1] = c[f2];
    c[f2] = tmp;
}

double Evluation(Chromo &c) { return tsp::getPathLength(c); }

vector<double> GA() {
    srand(time(NULL));
    /* ========== Initialization ========== */
    vector<Chromo> P(POP), P_next(POP);
    vector<double> fitness(POP);
    double best_fitness = 0.0;
    vector<double> result_v;

    for (int ci = 0; ci < POP; ci++)
        InitialChromosome(P.at(ci));

    /* ========== Iteration ========== */
    for (int ii = 0; ii < ITERATION; ii++) {

        /* ========== Evaluation ========== */
        for (int ci = 0; ci < POP; ci++) {
            fitness[ci] = Evluation(P[ci]);
            best_fitness = best_fitness > fitness[ci] ? best_fitness : fitness[ci];
            result_v.push_back(best_fitness);
        }

        /* ========== Selection ========== */
        Selection(P_next, P, fitness);

        /* ========== Crossover ========== */
        for (int ci = 0; ci < POP; ci += 2) {
            if ((double)rand() < C_RATE)
                Crossover(P_next.at(ci), P_next.at(ci + 1));
        }

        /* ========== Mutation ========== */
        for (int ci = 0; ci < POP; ci++) {
            if ((double)rand() < M_RATE)
                Mutation(P_next.at(ci));
        }

        /* ========== Determination ========== */
        P = P_next;
    }

    return result_v;
}

} // namespace ga