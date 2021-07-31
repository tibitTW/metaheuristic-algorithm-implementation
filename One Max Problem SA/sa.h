#include "onemax.h"

#include <stdlib.h>

double P(int new_f, int f, double temp) { return exp((-1) * (new_f + f) / temp); }

void SA(const int BIT_SIZE, const int ITERATION, const double INIT_TEMP, double TEMP_COOLDOWN_RATE, const bool F_TYPE, const bool NB_TYPE,
        const int N, int *result) {
    bool *sol = (bool *)malloc(sizeof(bool) * BIT_SIZE);
    bool *nbsol = (bool *)malloc(sizeof(bool) * BIT_SIZE);
    unsigned f, nb_f, best_f = 0;
    double temp = INIT_TEMP;

    // -------- Initialization -------- //
    best_f = 0;
    temp = INIT_TEMP;
    initSolution(sol, BIT_SIZE);

    // -------- Evalutation -------- //
    if (!F_TYPE) {
        f = onemaxFitness(sol, BIT_SIZE);
    } else {
        f = deceptionFitness(sol, BIT_SIZE, N);
    }

    best_f = f;
    result[0] = best_f;

    // iteration
    for (int iter = 1; iter <= ITERATION; iter++) {
        // -------- Transition -------- //
        updateNeighborSolution(nbsol, sol, BIT_SIZE, NB_TYPE, rand() % 2);

        // -------- Evalutation -------- //
        if (!F_TYPE) {
            nb_f = onemaxFitness(nbsol, BIT_SIZE);
        } else {
            nb_f = deceptionFitness(nbsol, BIT_SIZE, N);
        }

        // -------- Determination -------- //
        double r = (double)rand() / RAND_MAX;

        if (r < P(nb_f, f, temp)) {
            solcpy(sol, nbsol, BIT_SIZE);

            f = nb_f;
            best_f = f > best_f ? f : best_f;
        }

        result[iter] = best_f;
        temp *= TEMP_COOLDOWN_RATE;
    }
}