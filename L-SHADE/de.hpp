#include <cstdio>
#include <ctime>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>

using namespace std;

class DE {
    // solution datatype
    typedef vector<double> Solution;
    typedef vector<double> Mutated_V;
    typedef vector<Solution> Population;

  private:
    /* = = = = = = = = = = =   Parameters   = = = = = = = = = = = */
    // initial crossover rate
    const double NUM_CR_INIT = 0.5;
    // initial scaling factor rate
    const double NUM_F_INIT = 0.5;
    // terminal value
    const int TM_VAL = -1;
    const int N_MIN = 4;

    // initial number of population
    int NUM_NP_INIT;
    // number of population
    int num_NP;
    // number of x dimension
    int NUM_X_DIM;
    // minimum number of x
    int NUM_X_MIN;
    // max value of x
    int NUM_X_MAX;

    // maximum number of fitness evaluations
    int NUM_MAX_NFE;

    // current number of fitness evaluations
    int num_nfe;

    // num of generation
    int g;
    // control parameter p (in pbest)
    double ctrl_p;
    // size of M_CR
    int H;

    vector<double> ARR_CR, ARR_SF;
    vector<double> S_CR, S_SF;
    vector<double> M_CR, M_SF;

    /* = = = = = = = = = = =   random objects   = = = = = = = = = = = */
    random_device _rd;
    default_random_engine generator;
    uniform_real_distribution<double> zero_one_dt;
    uniform_real_distribution<double> x_val_dt;
    uniform_int_distribution<int> si_dt;
    uniform_int_distribution<int> xi_dt;

    Population P, V, U;
    // fitness table of P and U
    vector<double> ARR_F, ARR_F_U;
    double best_fitness = 0;
    /* = = = = = = = = = =   quick sort   = = = = = = = = = = */

    void swap_idx(int a, int b) {
        // swap(ARR_CR[a], ARR_CR[b]);
        double lf_tmp = ARR_CR.at(a);
        ARR_CR.at(a) = ARR_CR.at(b);
        ARR_CR.at(b) = lf_tmp;

        // swap(ARR_SF[a], ARR_SF[b]);
        lf_tmp = ARR_SF.at(a);
        ARR_SF.at(a) = ARR_SF.at(b);
        ARR_SF.at(b) = lf_tmp;

        // swap(P[a], P[b]);
        Solution sol_tmp = P.at(a);
        P.at(a) = P.at(b);
        P.at(b) = sol_tmp;
    }
    void swap_solution(Solution &s1, Solution &s2) {
        Solution s_tmp = s1;
        s1 = s2;
        s2 = s_tmp;
    }
    int partition(int front, int end) {
        double pivot = ARR_F[end];
        int i = front - 1;
        for (int j = front; j < end; j++) {
            if (ARR_F[j] < pivot) {
                i++;
                swap_idx(i, j);
            }
        }
        i++;
        swap_idx(i, end);
        return i;
    }
    void quick_sort(int front, int end) {
        if (front >= end)
            return;

        int pivot_idx = partition(front, end);
        quick_sort(front, pivot_idx - 1);
        quick_sort(pivot_idx + 1, end);
    }
    void initialization() {
        ARR_CR.resize(NUM_NP_INIT);
        ARR_SF.resize(NUM_NP_INIT);

        // initialize number of generation
        g = 1;

        // initialize number of population
        num_NP = NUM_NP_INIT;

        // TODO : archive A = empty vector

        for (int si = 0; si < num_NP; si++) {
            // initialize population P
            for (int xi = 0; xi < NUM_X_DIM; xi++)
                P.at(si).at(xi) = x_val_dt(generator);

            // initialize M_CR, M_F
            M_CR.at(si) = NUM_CR_INIT;
            M_SF.at(si) = NUM_F_INIT;
        }
    }
    void mutation() {
        uniform_int_distribution<int> s_dt(0, num_NP - 1);
        uniform_int_distribution<int> ps_dt(0, (int)ctrl_p * num_NP);
        double r_pb, r1, r2;
        for (int si = 0; si < num_NP; si++) {

            // choose pbest random solution
            r_pb = ps_dt(generator);
            // choose 2 random solution differently
            r1 = s_dt(generator);
            r2 = s_dt(generator);
            while (r1 == r2)
                r2 = s_dt(generator);

            for (int xi = 0; xi < NUM_X_DIM; xi++) {
                V.at(si).at(xi) =
                    P.at(si).at(xi) + ARR_SF.at(si) * (P.at(r_pb).at(xi) - P.at(si).at(xi) + P.at(r1).at(xi) - P.at(r2).at(xi));
                if (V.at(si).at(xi) < NUM_X_MIN)
                    V.at(si).at(xi) = (NUM_X_MIN + P.at(si).at(xi)) / 2;
                if (V.at(si).at(xi) > NUM_X_MAX)
                    V.at(si).at(xi) = (NUM_X_MAX + P.at(si).at(xi)) / 2;
            }
        }
    }
    void crossover() {
        for (int si = 0; si < num_NP; si++) {
            for (int xi = 0; xi < NUM_X_DIM; xi++) {
                if (zero_one_dt(generator) <= ARR_CR.at(si) || xi == xi_dt(generator))
                    U.at(si).at(xi) = V.at(si).at(xi);
                else
                    U.at(si).at(xi) = P.at(si).at(xi);
            }
        }
    }
    void selection() {
        for (int si = 0; si < num_NP; si++) {
            if (ARR_F_U.at(si) <= ARR_F.at(si)) {
                ARR_F.at(si) = ARR_F_U.at(si);
                P.at(si) = U.at(si);
            }
        }
    }

    /* = = = = = = = =   functions for debugging   = = = = = = = = */
    void printP() {
        for (auto sol : P) {
            for (auto x : sol)
                cout << x << "\t";
            cout << endl;
        }
    }

  public:
    // constructor
    DE(int num_np_init, int num_max_nfe, int num_x_dim, int num_x_min, int num_x_max) {
        NUM_MAX_NFE = num_max_nfe;
        NUM_X_DIM = num_x_dim;
        NUM_X_MIN = num_x_min;
        NUM_X_MAX = num_x_max;
        NUM_NP_INIT = num_np_init;
        num_NP = num_np_init;

        P.clear();
        V.clear();
        for (int si = 0; si < NUM_NP_INIT; si++) {
            P.push_back(Solution(NUM_X_DIM, 0));
            V.push_back(Solution(NUM_X_DIM, 0));
        }

        // initialize random generator & distribution
        generator.seed(_rd());
        x_val_dt.param(uniform_real_distribution<double>(NUM_X_MIN, NUM_X_MAX).param());
        zero_one_dt.param(uniform_real_distribution<double>(0., 1.).param());
        xi_dt.param(uniform_int_distribution<int>(0, NUM_X_DIM - 1).param());
    }

    // test function
    void test() {}

    // run L-SHADE algorithm (main structure)
    double run() {
        /* ======== Initialization ======== */
        initialization();

        // while (the termination criteria are not met)
        while (num_nfe < NUM_MAX_NFE) {
            // clear S_CR & S_F
            S_CR.clear();
            S_SF.clear();

            // TODO : Parameter update (CR, F)
            si_dt.param(uniform_int_distribution<int>(0, num_NP - 1).param());
            for (int si = 0; si < num_NP; si++) {
                int ri = si_dt(generator);
            }

            // sort(0, num_NP);
            mutation();
            crossover();
            // TODO : Evaluation
            // TODO : sort

            selection();

            num_NP = (int)round((N_MIN - NUM_NP_INIT) / NUM_MAX_NFE * g + NUM_NP_INIT);
            // TODO : 刪掉超出 num_NP 範圍的個體，從排名最後開始刪
            g++;
        }
    }
};