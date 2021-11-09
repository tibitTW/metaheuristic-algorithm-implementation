#include "cec17_test_func.h"

#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
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
    // DEBUG
    fstream check_file;

    /* = = = = = = = = = = =   Parameters   = = = = = = = = = = = */
    // initial crossover rate
    const double NUM_CR_INIT = 0.5;
    // initial scaling factor rate
    const double NUM_F_INIT = 0.5;
    // parameter memory size
    int H;
    // terminal value
    const int TM_VAL = -1;
    const int N_MIN = 4;

    // initial number of population
    const int NUM_NP_INIT = 100;
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

    // FIXME
    // control parameter p (in pbest)
    const double ctrl_p = 0.1;

    // cec benchmark fitness function number
    int FUNC_NUM;

    vector<double> ARR_CR, ARR_SF;
    vector<double> S_CR, S_SF;
    vector<double> M_CR, M_SF;

    Population P, V, U, A;

    // fitness table
    vector<double> ARR_F, ARR_F_U;
    double best_fitness = 0;
    /* = = = = = = = = = = =   random objects   = = = = = = = = = = = */
    random_device rd;
    mt19937 generator{rd()};
    uniform_real_distribution<double> zero_one_dt;
    uniform_real_distribution<double> x_val_dt;
    uniform_int_distribution<int> si_dt;
    uniform_int_distribution<int> xi_dt;

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

        // swap(ARR_F[a], ARR_F[b]);
        lf_tmp = ARR_F.at(a);
        ARR_F.at(a) = ARR_F.at(b);
        ARR_F.at(b) = lf_tmp;

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

    /* = = = = = = = = = =   L_SHADE functions   = = = = = = = = = = */
    void initialization() {

        ARR_CR.resize(NUM_NP_INIT);
        ARR_SF.resize(NUM_NP_INIT);

        ARR_F.resize(NUM_NP_INIT);
        ARR_F_U.resize(NUM_NP_INIT);

        P.clear();
        V.clear();
        U.clear();
        for (int si = 0; si < NUM_NP_INIT; si++) {
            P.push_back(Solution(NUM_X_DIM, 0));
            V.push_back(Solution(NUM_X_DIM, 0));
            U.push_back(Solution(NUM_X_DIM, 0));
        }

        // number of generation
        g = 1;
        // number of evaluation
        num_nfe = 0;
        // number of population
        num_NP = NUM_NP_INIT;
        // archive
        A.clear();

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

            if (ARR_F_U.at(si) < ARR_F.at(si)) {
                A.push_back(P.at(si));
                S_CR.push_back(ARR_CR.at(si));
                S_SF.push_back(ARR_SF.at(si));
            }
        }
    }
    void evaluation() {
        for (int si = 0; si < num_NP; si++) {
            cec17_test_func(&P.at(si).at(0), &ARR_F.at(si), NUM_X_DIM, 1, FUNC_NUM);
            num_nfe++;
        }
    }
    void evaluation_U() {
        for (int si = 0; si < num_NP; si++) {
            cec17_test_func(&U.at(si).at(0), &ARR_F_U.at(si), NUM_X_DIM, 1, FUNC_NUM);
            num_nfe++;
        }
    }

    /* = = = = = = = =   functions for debugging   = = = = = = = = */
    void printP(Population Pop) {
        for (auto sol : Pop) {
            for (auto x : sol)
                check_file << setw(8) << fixed << setprecision(4) << x << "\t";
            check_file << endl;
        }
    }

  public:
    // constructor
    DE(int num_max_nfe, int num_x_dim, int num_x_min, int num_x_max, int fun_num) {
        // DEBUG
        check_file.open("check.txt", ios::out | ios::trunc);

        NUM_MAX_NFE = num_max_nfe;
        NUM_X_DIM = num_x_dim;
        NUM_X_MIN = num_x_min;
        NUM_X_MAX = num_x_max;
        num_NP = NUM_NP_INIT;
        FUNC_NUM = fun_num;

        M_CR.resize(H);
        M_SF.resize(H);

        // initialize random generator & distribution
        generator.seed(rd());
        x_val_dt.param(uniform_real_distribution<double>(NUM_X_MIN, NUM_X_MAX).param());
        zero_one_dt.param(uniform_real_distribution<double>(0., 1.).param());
        xi_dt.param(uniform_int_distribution<int>(0, NUM_X_DIM - 1).param());
    }

    // test function
    void test() {}

    // run L-SHADE algorithm (main structure)
    double run() {
        initialization();
        // DEBUG
        check_file << "==========    Initialization     ==========\n";
        check_file << "size of ARR_CR: " << ARR_CR.size() << endl;
        check_file << "size of ARR_SF: " << ARR_SF.size() << endl;
        check_file << "g: " << g << endl;
        check_file << "size of archive: " << A.size() << endl;
        check_file << "population:" << endl;
        printP(P);

        // while (the termination criteria are not met)
        while (num_nfe < NUM_MAX_NFE) {
            // DEBUG
            check_file << "iteration: " << g << endl;
            // DEBUG END

            // clear S_CR & S_F
            S_CR.clear();
            S_SF.clear();

            // control parameters update
            si_dt.param(uniform_int_distribution<int>(0, H - 1).param());
            for (int si = 0; si < num_NP; si++) {
                int ri = si_dt(generator);
                if (M_CR.at(ri) == TM_VAL) {
                    ARR_CR.at(si) = 0;
                } else {
                    normal_distribution<> nm_dt{M_CR.at(ri), 0.1};
                    ARR_CR.at(si) = nm_dt(generator);
                    ARR_CR.at(si) = ARR_CR.at(si) > 1 ? 1 : ARR_CR.at(si);
                    ARR_CR.at(si) = ARR_CR.at(si) < 0 ? 0 : ARR_CR.at(si);
                }
                cauchy_distribution<> cc_dt{M_SF.at(ri), 0.1};
                ARR_SF.at(si) = cc_dt(generator);
                // re-generate new number until number > 0
                while (ARR_SF.at(si) <= 0)
                    ARR_SF.at(si) = cc_dt(generator);

                ARR_SF.at(si) = ARR_SF.at(si) > 1 ? 1 : ARR_SF.at(si);
            }

            // DEBUG
            // check_file << "control parameters updated." << endl;

            mutation();

            // DEBUG
            // check_file << "mutation completed." << endl;

            crossover();

            // DEBUG
            // check_file << "crossover completed." << endl;

            evaluation();

            // DEBUG
            // check_file << "evaluation completed." << endl;

            evaluation_U();

            // DEBUG
            // check_file << "evaluation_U completed." << endl;

            selection();

            // DEBUG
            // check_file << "selection completed." << endl;

            // sort
            quick_sort(0, num_NP - 1);

            // DEBUG
            // for (auto f : ARR_F)
            //     check_file << f << endl;
            // check_file << endl;

            num_NP = (int)round((double)(N_MIN - NUM_NP_INIT) * num_nfe / NUM_MAX_NFE + NUM_NP_INIT);

            // resize
            P.resize(num_NP);
            U.resize(num_NP);
            V.resize(num_NP);
            ARR_CR.resize(num_NP);
            ARR_SF.resize(num_NP);
            ARR_F.resize(num_NP);

            g++;
        }
        return ARR_F.at(0);
    }
};