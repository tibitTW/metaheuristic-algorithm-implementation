#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// solution datatype
typedef vector<double> Solution;
typedef vector<double> Mutated_V;
typedef vector<Solution> Population;

class DE {
    void initialization(Population &P, const int NP, const int X_DIM, const double X_MIN, const double X_MAX) {
        for (int si = 0; si < NP; si++) {
            for (int xi = 0; xi < X_DIM; xi++) {
                P.at(si).at(xi) = unif(generator);
            }
        }
    }

    // current-to-pbest/1
    void mutation(Population &P, Population &V, const int NP, const int NUM_X_DIM) {
        Mutated_V v_tmp(NUM_X_DIM);
        double r1, r2;
        for (int si = 0; si < NP; si++) {
        }
    }

    void crossover() {}

    void selection() {}

    double run(const double NUM_CR, const double NUM_F, const int NUM_NP_init, const int NUM_MAX_ITER, const int NUM_X_DIM,
               const int NUM_X_MIN, const int NUM_X_MAX) {

        /* ======== Initialization ======== */
        // random number generator
        random_device rd;
        default_random_engine generator(rd());
        uniform_real_distribution<double> unif(NUM_X_MIN, NUM_X_MAX);

        // number of generation
        int g = 1;
        // number of population
        int NUM_NP = NUM_NP_init;
        // Archive
        Population A;
        // Population
        Population P(NUM_NP_init, Solution(NUM_X_DIM, 0.0)), V(NUM_NP_init, Solution(NUM_X_DIM, 0.0)),
            U(NUM_NP_init, Solution(NUM_X_DIM, 0.0));
        initialization(P, NUM_NP, NUM_X_DIM, NUM_X_MIN, NUM_X_MAX);
        vector<double> M_CR(NUM_NP, 0.5), M_F(NUM_NP, 0.5);

        while (g <= NUM_MAX_ITER) {
            for (int si = 0; si < NUM_NP; si++) {
                /* ======== Parameter update (CR, F) ======== */
                /* ======== Mutation ======== */
                mutation(4, P, V, NUM_X_DIM);
                /* ======== Crossover ======== */
                crossover();
                /* ======== Selection ======== */
            }
        }
    }
}
