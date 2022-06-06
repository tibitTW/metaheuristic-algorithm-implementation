#include "test_function.hpp"

#include <limits>
#include <random>
#include <vector>

// * debug
#include <cstdio>
#include <iostream>
using namespace std;

class DE {
    typedef vector<double> d1d; // 1d double array
    typedef vector<d1d> d2d;    // 2d double array
    typedef d2d P;              // population

  private:
    int NP, G, FES, MAX_FES, X_DIM, TEST_FUNC_ID;
    double CR, F, X_MIN, X_MAX;
    P X, V, U;
    d1d X_fitness;
    double best_fitness;
    d1d best_fitness_arr;

    // random object
    random_device rd;
    mt19937 generator{rd()};
    uniform_real_distribution<double> unif{0.0, 1.0};

    void Initialization();
    void Mutation();
    void Crossover();
    void Evaluation();

  public:
    DE(int NP, double CR, double F, double MAX_FES, int X_DIM, double X_MIN, double X_MAX,
       int TEST_FUNC_ID);
    d1d run(int RUN_NUM);
};

DE::DE(int NP, double CR, double F, double MAX_FES, int X_DIM, double X_MIN, double X_MAX,
       int TEST_FUNC_ID) {
    this->NP = NP;
    this->CR = CR;
    this->F = F;
    this->MAX_FES = MAX_FES;
    this->X_DIM = X_DIM;
    this->X_MIN = X_MIN;
    this->X_MAX = X_MAX;
    this->TEST_FUNC_ID = TEST_FUNC_ID;

    X.assign(NP, d1d(X_DIM, 0));
    V.assign(NP, d1d(X_DIM, 0));
    U.assign(NP, d1d(X_DIM, 0));

    X_fitness.resize(NP);
}

void DE::Initialization() {
    best_fitness = std::numeric_limits<double>::max();
    G = 0;
    FES = 0;
    best_fitness_arr.clear();

    for (int pi = 0; pi < NP; pi++) {
        for (int xi = 0; xi < X_DIM; xi++)
            X.at(pi).at(xi) = unif(generator) * (X_MAX - X_MIN) + X_MIN;
        X_fitness.at(pi) = test_func(X.at(pi), TEST_FUNC_ID);
        best_fitness = X_fitness.at(pi) < best_fitness ? X_fitness.at(pi) : best_fitness;
        best_fitness_arr.push_back(best_fitness);
    }

    FES += NP;
}

void DE::Mutation() {
    for (int pi = 0; pi < NP; pi++) {
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
        for (int xi = 0; xi < X_DIM; xi++) {
            V.at(pi).at(xi) = X.at(r1).at(xi) + F * (X.at(r2).at(xi) - X.at(r3).at(xi));
            if (V.at(pi).at(xi) < X_MIN)
                V.at(pi).at(xi) *= -1;
            if (V.at(pi).at(xi) > X_MAX)
                V.at(pi).at(xi) = 2 * X_MAX - V.at(pi).at(xi);
        }
    }
}

void DE::Crossover() {
    int rnd;
    for (int pi = 0; pi < NP; pi++) {
        rnd = (int)(unif(generator)) * X_DIM;
        for (int xi = 0; xi < X_DIM; xi++) {
            if (unif(generator) <= CR || xi == rnd)
                U.at(pi).at(xi) = V.at(pi).at(xi);
            else
                U.at(pi).at(xi) = X.at(pi).at(xi);
        }
    }
}

void DE::Evaluation() {
    for (int pi = 0; pi < NP; pi++) {
        double fitness = test_func(U.at(pi), TEST_FUNC_ID);

        if (fitness <= X_fitness.at(pi)) {

            X_fitness.at(pi) = fitness;
            X.at(pi) = U.at(pi);
            best_fitness = fitness < best_fitness ? fitness : best_fitness;
        }
        best_fitness_arr.push_back(best_fitness);
    }

    // * debug
    // for (int pi = 0; pi < NP; pi++) {
    //     cout << X_fitness.at(pi) << endl;
    // }
    // cout << "\n";

    FES += NP;
}

d1d DE::run(int RUN_NUM) {
    d1d best_fitness_sum_arr(MAX_FES, 0);

    for (int ri = 0; ri < RUN_NUM; ri++) {
        Initialization();

        // main loop
        while (FES < MAX_FES) {
            Mutation();
            Crossover();
            Evaluation();

            G++;
        }

        for (int i = 0; i < best_fitness_sum_arr.size(); i++)
            best_fitness_sum_arr.at(i) += best_fitness_arr.at(i);
    }

    for (int i = 0; i < best_fitness_sum_arr.size(); i++)
        best_fitness_sum_arr.at(i) /= RUN_NUM;

    return best_fitness_sum_arr;
}
