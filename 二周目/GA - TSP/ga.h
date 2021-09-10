#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>

typedef vector<int> Chromo;
using namespace std;

void InitialChromosome(Chromo &c, const int CITY_DIM) {
    c.clear();
    //
}
void Crossover(Chromo &c1, Chromo &c2) {
    // TODO: 3 versions of crossover
    // 1. partially mapped crossover
    // 2. cycle crossover
    // 3. order crossover
}
void Mutation(Chromo &c) {
    // TODO: 確認怎麼做TSP的Mutation
}
double Evluation(Chromo &c) {}

int GA(const int POP, const int CITY_DIM, const int ITERATION, const double C_RATE, const double M_RATE) {
    srand(time(NULL));
    /* ========== Initialization ========== */
    vector<Chromo> P(POP);
    for (int ci = 0; ci < POP; ci++)
        InitialChromosome(P.at(ci), CITY_DIM);

    /* ========== Iteration ========== */
    for (int ii = 0; ii < ITERATION; ii++) {
        /* ========== Transition ========== */
        // crossover
        for (int ci = 0; ci < POP; ci += 2) {
            if ((double)rand() < C_RATE)
                Crossover(P.at(ci), P.at(ci + 1));
        }
        // mutation
        for (int ci = 0; ci < POP; ci++) {
            if ((double)rand() < M_RATE)
                Mutation(P.at(ci));
        }

        /* ========== Evluation ========== */

        /* ========== Determination ========== */
    }

    return -1;
}