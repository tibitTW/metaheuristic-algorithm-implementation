#include "config.h"
#include "tsp.h"
#include <cstdlib>
#include <iostream>
#include <set>
#include <time.h>
#include <vector>

typedef vector<int> Chromo;
typedef vector<Chromo> Chromo_P;
using namespace std;

namespace ga {

void InitialChromosome(Chromo &c) { c = tsp::getRandomPath(); }

// TODO
// partially mapped crossover
void PMX(Chromo &c1, Chromo &c2) {

    // set start and stop point of substring
    int flag1 = rand() % CITY_DIM, flag2 = rand() % (CITY_DIM - 1);
    if (flag1 > flag2) {
        int tmp = flag1;
        flag1 = flag2;
        flag2 = tmp;
    } else {
        flag2 += 1;
    }

    vector<set<int>> pairs;
    set<int> pair_tmp;
    vector<int> used(flag2 - flag1 + 1, 0);

    for (int i = flag1; i <= flag2; i++) {
        if (!used[i - flag1]) {
            pair_tmp.clear();
            pair_tmp.insert(c1[i]);
            pair_tmp.insert(c2[i]);
            for (int j = i + 1; j <= flag2; j++) {
                for (int num : pair_tmp) {
                    if (num == c1[j] || num == c2[j]) {
                        pair_tmp.insert(c1[j]);
                        pair_tmp.insert(c2[j]);
                        used[j - flag1] = 1;
                    }
                }
            }
            pairs.push_back(pair_tmp);
        }
    }

    // TODO: switch substring 以外的部分
}

// cycle crossover ✔
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

    int tmp;
    for (int ci = 0; ci < CITY_DIM; ci++) {
        if (mask[ci]) {
            tmp = c1[ci];
            c1[ci] = c2[ci];
            c2[ci] = tmp;
        }
    }
}

// TODO
// order crossover
void OX(Chromo &c1, Chromo &c2) {}
void OX(Chromo &c1, Chromo &c2) {
    Chromo new_c1, new_c2;

    int flag1 = rand() % CITY_DIM, flag2 = rand() % (CITY_DIM - 1);
    if (flag1 > flag2) {
        int tmp = flag1;
        flag1 = flag2;
        flag2 = tmp;
    } else {
        flag2 += 1;
    }

    bool is_in_substring;
    for (int i = flag2 + 1; i < CITY_DIM; i++) {
        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c1[i] == c2[fi]) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c1.push_back(c1[i]);
        }

        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c2[i] == c1[fi]) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c2.push_back(c2[i]);
        }
    }
    for (int i = 0; i < flag1; i++) {
        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c1[i] == c2[fi]) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c1.push_back(c1[i]);
        }
        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c2[i] == c1[fi]) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c2.push_back(c2[i]);
        }
    }

    for (int i = flag1; i <= flag2; i++) {
        new_c1.push_back(c1[i]);
        new_c2.push_back(c2[i]);
    }
    for (int i = flag1; i <= flag2; i++) {
        new_c1.push_back(c2[i]);
        new_c2.push_back(c1[i]);
    }

    int ci = flag2 + 1;
    for (int i = 0; i < CITY_DIM; i++) {
        c1[ci] = new_c1[i];
        c2[ci] = new_c2[i];
        ci++;
        ci = (ci == CITY_DIM) ? 0 : ci;
    }
}

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

// roulette wheel selection
void RWS(Chromo_P &P_next, Chromo_P P, vector<double> fitness) {
    double fitness_sum = 0;
    vector<double> fitness_P_table(POP, 0);

    for (int ci = 0; ci < POP; ci++)
        fitness_sum += (double)1 / fitness[ci];

    for (int ci = 0; ci < POP; ci++) {
        fitness_P_table[ci] = (double)1 / fitness[ci] / fitness_sum;
        if (ci != 0)
            fitness_P_table[ci] += fitness_P_table[ci - 1];
    }

    for (int ci = 0; ci < POP; ci++) {
        double flag = (double)rand() / RAND_MAX;
        for (int cj = 0; cj < POP; cj++) {
            if (fitness_P_table[cj] > flag) {
                P_next[ci] = P[cj];
                break;
            }
        }
    }
}
// TODO
// tournament selection
void TS(Chromo_P &P_next, Chromo_P P, vector<double> fitness) {}
// TODO: tournament selection
void TS(Chromo_P &P_next, Chromo_P P, vector<double> fitness) {

    for (int ci = 0; ci < POP; ci++) {
        // choose a Chromo
    }
}
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

double Evluation(Chromo c) { return tsp::getPathLength(c); }

vector<double> GA() {
    /* ========== Initialization ========== */
    vector<Chromo> P(POP), P_next(POP);
    vector<double> fitness(POP);
    double best_fitness = INFINITY;
    vector<double> result_v;

    for (int ci = 0; ci < POP; ci++)
        InitialChromosome(P[ci]);

    /* ========== Iteration ========== */
    for (int ii = 0; ii < ITERATION; ii++) {

        /* ========== Evaluation ========== */
        for (int ci = 0; ci < POP; ci++) {
            fitness[ci] = Evluation(P[ci]);
            best_fitness = best_fitness < fitness[ci] ? best_fitness : fitness[ci];
        }

        result_v.push_back(best_fitness);

        /* ========== Selection ========== */
        Selection(P_next, P, fitness);

        /* ========== Crossover ✔ ========== */
        for (int ci = 0; ci < POP; ci += 2) {
            if ((double)rand() / RAND_MAX < C_RATE)
                Crossover(P_next.at(ci), P_next.at(ci + 1));
        }

        /* ========== Mutation ✔ ========== */
        for (int ci = 0; ci < POP; ci++) {
            if ((double)rand() / RAND_MAX < M_RATE)
                Mutation(P_next.at(ci));
        }

        /* ========== Determination ✔ ========== */
        P = P_next;
    }

    return result_v;
}

} // namespace ga