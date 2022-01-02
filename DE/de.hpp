#include "ackley.hpp"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class de {
    typedef vector<int> i1d;
    typedef vector<i1d> i2d;
    typedef vector<double> d1d;
    typedef vector<d1d> d2d;

    // population
    typedef d2d P;

  private:
    int NP, G, FES, MAX_FES, X_DIM;
    double CR, F, X_MIN, X_MAX;

    P X, V, U;
    d1d X_fitness;
    double best_fitness;

    // random object
    random_device rd;
    mt19937 generator{rd()};
    uniform_real_distribution<double> unif{0.0, 1.0};

    void initialization();

  public:
    de(int NP, double CR, double F, double MAX_FES, int X_DIM, double X_MIN, double X_MAX);
    double run();
};

de::de(int NP, double CR, double F, double MAX_FES, int X_DIM, double X_MIN, double X_MAX) {
    this->NP = NP;
    this->CR = CR;
    this->F = F;
    this->MAX_FES = MAX_FES;
    this->X_DIM = X_DIM;
    this->X_MIN = X_MIN;
    this->X_MAX = X_MAX;

    X.assign(NP, d1d(X_DIM, 0));
    V.assign(NP, d1d(X_DIM, 0));
    U.assign(NP, d1d(X_DIM, 0));
    X_fitness.resize(NP);
}
double de::run() {
    best_fitness = 1.0E10;
    G = 0;
    FES = 0;
    /* --------------- INITIALIZATION --------------- */
    for (int pi = 0; pi < NP; pi++) {
        for (int xi = 0; xi < X_DIM; xi++)
            X.at(pi).at(xi) = unif(generator) * (X_MAX - X_MIN) + X_MIN;
        X_fitness.at(pi) = ackley(X.at(pi));
        best_fitness = X_fitness.at(pi) < best_fitness ? X_fitness.at(pi) : best_fitness;
    }

    while (FES < MAX_FES) {
        for (int pi = 0; pi < NP; pi++) {
            /* ---------------- MUTATION ---------------- */
            // generate xr1, xr2, xr3
            int r1 = (int)(unif(generator) * (NP - 1));
            int r2 = (int)(unif(generator) * (NP - 2));
            int r3 = (int)(unif(generator) * (NP - 3));
            r1 += (pi <= r1);
            r2 += (pi <= r2) + (r1 <= r2);
            while (r2 == pi || r2 == r1) {
                r2++;
                r2 = r2 == NP ? 0 : r2;
            }
            r3 += (pi <= r3) + (r1 <= r3) + (r2 <= r3);
            while (r3 == pi || r3 == r1 || r3 == r2) {
                r3++;
                r3 = r3 == NP ? 0 : r3;
            }
            for (int xi = 0; xi < X_DIM; xi++)
                V.at(pi).at(xi) = X.at(r1).at(xi) + F * (X.at(r3).at(xi) - X.at(r3).at(xi));
            /* --------------- CROSSOVER ---------------- */
            for (int xi = 0; xi < X_DIM; xi++) {
                if (unif(generator) <= CR || xi == (int)(unif(generator)))
                    U.at(pi).at(xi) = V.at(pi).at(xi);
                else
                    U.at(pi).at(xi) = X.at(pi).at(xi);
            }
            /* --------------- EVALUATION --------------- */
            double fitness = ackley(U.at(pi));
            if (fitness <= X_fitness.at(pi)) {
                X.at(pi) = U.at(pi);
                X_fitness.at(pi) = fitness;
                best_fitness = fitness < best_fitness ? fitness : best_fitness;
            }
        }
        FES += NP;
        G++;
    }
    return best_fitness;
}
