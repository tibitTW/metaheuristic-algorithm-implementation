#include "onemax.h"
#include <iostream>
#include <stdlib.h>

#define Q_SIZE 7

using std::cout;
using std::endl;

void TS(const int BIT_SIZE, const int ITERATION, const int TS_TYPE, int *resultArr) {
    bool *solQueue[Q_SIZE];
    for (int qi = 0; qi < Q_SIZE; qi++) {
        solQueue[qi] = (bool *)malloc(sizeof(bool) * BIT_SIZE);
        for (int bi = 0; bi < BIT_SIZE; bi++)
            solQueue[qi][bi] = 0;
    }
    int qidx = 0, qtail = 0;

    // ======== Initialzation ======== //
    bool *sol = (bool *)malloc(BIT_SIZE * sizeof(int));
    initSolution(sol, BIT_SIZE);
    solcpy(solQueue[0], sol, BIT_SIZE);
    qidx++;
    qtail++;

    // ======== Evaluation ======== //
    int fitness = onemaxFitness(sol, BIT_SIZE);
    int best_fitness = fitness;
    resultArr[0] = best_fitness;

    bool *nbsol = (bool *)malloc(BIT_SIZE * sizeof(int));
    int nb_fitness;

    for (int ii = 1; ii <= ITERATION; ii++) {
        /* ======== Transition ======== */
        updateNeighborSolution(nbsol, sol, BIT_SIZE, 1, -1);

        /* ======== Evaluation ======== */
        nb_fitness = onemaxFitness(nbsol, BIT_SIZE);

        /* ======== Determination ======== */
        if (nb_fitness > fitness) {
            if (qtail != Q_SIZE) {
                fitness = nb_fitness;
                best_fitness = nb_fitness;
                solcpy(sol, nbsol, BIT_SIZE);
                solcpy(solQueue[qidx], sol, BIT_SIZE);
                qidx++;
                qtail++;
            } else {
                qidx %= Q_SIZE;
                bool is_in_queue = false;
                for (int qi = 0; qi < Q_SIZE; qi++) {
                    if (solcmp(nbsol, solQueue[qi], BIT_SIZE) == 0) {
                        is_in_queue = true;
                        break;
                    }
                }
                if (!is_in_queue) {
                    fitness = nb_fitness;
                    best_fitness = nb_fitness;
                    solcpy(sol, nbsol, BIT_SIZE);
                    solcpy(solQueue[qidx], sol, BIT_SIZE);
                    qidx++;
                }
            }
        }

        resultArr[ii] = best_fitness;
    }
}