#include <cstdio>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// solution datatype
typedef vector<double> Solution;
typedef vector<double> Mutated_V;
typedef vector<Solution> Population;

namespace DE {
void initialization(Population &P, const int NP, const int X_DIM, const double X_MIN, const double X_MAX) {
    // initialization about random
    random_device rd;
    default_random_engine generator(rd());
    uniform_real_distribution<double> unif(X_MIN, X_MAX);

    for (int si = 0; si < NP; si++) {
        for (int xi = 0; xi < X_DIM; xi++) {
            P.at(si).at(xi) = unif(generator);
        }
    }
}

void crossover();

/*
strategy_id:
0: rand/1
1: rand/2
2: best/1
3: current-to-best/1
*/
void mutation(int strategy_id, Population P) {
    switch (strategy_id) {
    // rand/1
    case 0:
        break;

    // rand/2
    case 1:
        break;

    // best/1
    case 2:
        break;

    // current-to-best/1
    case 3:
        break;

    // current-to-pbest/1
    case 4:
        break;

    default:
        break;
    }
}

void selection() {}

// DE(crossover_rate, scaling_factor, num_of_population)
// double DE(const double CR, const double F, const int NP, const int ITER, const int X_DIM, const double X_MIN, const double X_MAX) {

//     Population P(NP);
//     initialization(NP, ITER, X_DIM, X_MIN, X_MAX);
//     // generation number
//     int g = 0;

//     while (g < ITER) {
//         mutation(0, P);
//         crossover();
//         selection();
//     }
// }
// double SHADE(const double CR, const double F, const int NP, const int ITER, const int X_DIM) { initialization(NP, ITER, X_DIM); }
double L_SHADE(const double CR, const double F, const int NP_init, const int MAX_ITER, const int X_DIM, const int X_MIN, const int X_MAX) {

    /* ======== Initialization ======== */
    // generation number
    int g = 1;
    // number of population
    int NP = NP_init;
    // Archive
    Population A;
    // Population
    Population P(NP_init), V(NP_init);
    initialization(P, NP_init, X_DIM, X_MIN, X_MAX);
    vector<double> M_CR(NP, 0.5), M_F(NP, 0.5);

    while (g <= MAX_ITER) {
        vector<double> S_CR(), S_F();

        for (int si = 0; si < NP; si++) {
        }
    }
}
} // namespace DE