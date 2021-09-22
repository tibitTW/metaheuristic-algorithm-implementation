#include "config.h"
#include "tsp.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <set>
#include <time.h>
#include <vector>

using namespace std;

typedef vector<int> Chromo;
typedef vector<Chromo> Chromo_P;

namespace ga {

void InitialChromosome(Chromo &c) { c = tsp::getRandomPath(); }

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
    set<int> pair_tmp, used_num;
    vector<int> used(CITY_DIM, 0);
    vector<bool> mask1(CITY_DIM, 0), mask2(CITY_DIM, 0);

    for (int i = flag1; i <= flag2; i++) {
        if (!mask1.at(i)) {
            pair_tmp.clear();
            pair_tmp.insert(c1.at(i));
            pair_tmp.insert(c2.at(i));
            used_num.insert(c1.at(i));
            used_num.insert(c2.at(i));
            for (int j = i + 1; j <= flag2; j++) {
                for (int num : pair_tmp) {
                    if (num == c1.at(j) || num == c2.at(j)) {
                        pair_tmp.insert(c1.at(j));
                        pair_tmp.insert(c2.at(j));
                        used_num.insert(c1.at(j));
                        used_num.insert(c2.at(j));
                        mask1.at(j) = 1;
                        mask2.at(j) = 1;
                    }
                }
            }
            pairs.push_back(pair_tmp);
        }
    }

    int tmp;
    set<int> tmp_pair;
    for (int i = 0; i < CITY_DIM; i++) {
        if (i >= flag1 && i <= flag2) {
            tmp = c1.at(i);
            c1.at(i) = c2.at(i);
            c2.at(i) = tmp;

        } else if (used_num.count(c1.at(i))) {
            for (set<int> pair : pairs) {
                if (pair.count(c1.at(i))) {
                    for (int j = 0; j < CITY_DIM; j++) {
                        if ((j < flag1 || j > flag2) && !mask2.at(j) && pair.count(c2.at(j))) {
                            tmp = c1.at(i);
                            c1.at(i) = c2.at(j);
                            c2.at(j) = tmp;
                            mask1.at(i) = 1;
                            mask2.at(j) = 1;
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}

// cycle crossover ✔
void CX(Chromo &c1, Chromo &c2) {
    vector<int> mask(CITY_DIM, 1);
    int b = c1.at(0), e = c2.at(0);
    mask.at(0) = 0;
    while (b != e) {
        int ci = 0;
        while (e != c1.at(ci))
            ci++;
        mask.at(ci) = 0;
        e = c2.at(ci);
    }

    int tmp;
    for (int ci = 0; ci < CITY_DIM; ci++) {
        if (mask.at(ci)) {
            tmp = c1.at(ci);
            c1.at(ci) = c2.at(ci);
            c2.at(ci) = tmp;
        }
    }
}

// order crossover
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
            if (c1.at(i) == c2.at(fi)) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c1.push_back(c1.at(i));
        }

        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c2.at(i) == c1.at(fi)) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c2.push_back(c2.at(i));
        }
    }

    for (int i = 0; i < flag1; i++) {
        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c1.at(i) == c2.at(fi)) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c1.push_back(c1.at(i));
        }
        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c2.at(i) == c1.at(fi)) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c2.push_back(c2.at(i));
        }
    }

    for (int i = flag1; i <= flag2; i++) {
        new_c1.push_back(c1.at(i));
        new_c2.push_back(c2.at(i));
    }
    for (int i = flag1; i <= flag2; i++) {
        new_c1.push_back(c2.at(i));
        new_c2.push_back(c1.at(i));
    }

    int ci = flag2 + 1;
    for (int i = 0; i < CITY_DIM; i++) {
        c1.at(ci) = new_c1.at(i);
        c2.at(ci) = new_c2.at(i);
        ci++;
        ci = (ci == CITY_DIM) ? 0 : ci;
    }

    for (int n : c1) {
        if (n < 0 || n >= CITY_DIM)
            cout << n << endl;
    }
    for (int n : c2) {
        if (n < 0 || n >= CITY_DIM)
            cout << n << endl;
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
        fitness_sum += (double)1 / fitness.at(ci);

    for (int ci = 0; ci < POP; ci++) {
        fitness_P_table.at(ci) = (double)1 / fitness.at(ci) / fitness_sum;
        if (ci != 0)
            fitness_P_table.at(ci) += fitness_P_table.at(ci - 1);
    }

    for (int ci = 0; ci < POP; ci++) {
        double flag = (double)rand() / RAND_MAX;
        for (int cj = 0; cj < POP; cj++) {
            if (fitness_P_table.at(cj) > flag) {
                P_next.at(ci) = P.at(cj);
                break;
            }
        }
    }
}
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

    int tmp = c.at(f1);
    c.at(f1) = c.at(f2);
    c.at(f2) = tmp;
}

double Evluation(Chromo c) { return tsp::getPathLength(c); }

vector<double> GA() {
    /* ========== Initialization ========== */
    vector<Chromo> P(POP), P_next(POP);
    vector<double> fitness(POP);
    double best_fitness = INFINITY;
    vector<double> result_v;

    for (int ci = 0; ci < POP; ci++)
        InitialChromosome(P.at(ci));

    /* ========== Iteration ========== */
    for (int ii = 0; ii < ITERATION; ii++) {
        /* ========== Evaluation ========== */
        for (int ci = 0; ci < POP; ci++) {
            fitness.at(ci) = Evluation(P.at(ci));
            best_fitness = best_fitness < fitness.at(ci) ? best_fitness : fitness.at(ci);
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