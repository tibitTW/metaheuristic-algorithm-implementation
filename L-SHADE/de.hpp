#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class DE {
    // solution datatype
    typedef vector<double> Solution;
    typedef vector<double> Mutated_V;
    typedef vector<Solution> Population;

  private:
    /* = = = = = = = = = = =   Attributes   = = = = = = = = = = = */
    // initial crossover rate
    const double NUM_CR_init = 0.5;
    // initial scaling factor rate
    const double NUM_F_init = 0.5;
    // terminal value
    const int tm_val = -1;

    vector<double> ARR_CR, ARR_SF;

    // initial number of population
    int NUM_NP_INIT;
    int num_NP;
    // max iteration
    int NUM_MAX_ITER;
    // x dimension
    int NUM_X_DIM;
    // min value of x
    int NUM_X_MIN;
    // max value of x
    int NUM_X_MAX;

    // num of generation
    int g;
    // control parameter p (in pbest)
    double ctrl_p;

    /* = = = = = = = = = = =   random objects   = = = = = = = = = = = */
    random_device _rd;
    default_random_engine generator;
    uniform_real_distribution<double> zero_one_dt;
    uniform_real_distribution<double> x_val_dt;
    uniform_int_distribution<int> xi_dt;

    Population P, V, U;
    // fitness table of P and U
    vector<double> ARR_F, ARR_F_U;
    double best_fitness = 0;

    /* = = = = = = = = = =   L_SHADE functions   = = = = = = = = = = */
    // ! need to debug
    // this function sorts both population and fitness array for mutation strategies (pbest) and LPSR (linear population size reduction)
    // the result will sort by fitness (descend) uses quick sort
    void sort(int left, int right) {
        if (right - left < 2)
            return;
        uniform_int_distribution<int> rand_dt(left, right);

        // 1. select 3 index from [0, num_NP-1] randomly and choose the center one
        int r1 = rand_dt(generator), r2 = rand_dt(generator), r3 = rand_dt(generator), rnd;
        if (ARR_F.at(r1) > ARR_F.at(r2)) {
            if (ARR_F.at(r2) > ARR_F.at(r3))
                rnd = r2;
            else
                rnd = ARR_F.at(r1) > ARR_F.at(r3) ? r3 : r1;

        } else {
            if (ARR_F.at(r1) > ARR_F.at(r3))
                rnd = r1;
            else
                rnd = ARR_F.at(r2) > ARR_F.at(r3) ? r3 : r2;
        }
        // 2. set 2 index, head & tail
        Solution s_tmp;
        double f_tmp;
        int l = left, r = right;
        while (l < r) {
            while (ARR_F.at(l) < ARR_F.at(rnd))
                l++;
            while (ARR_F.at(rnd) < ARR_F.at(r))
                r--;

            // swap(F[l], F[r])
            f_tmp = ARR_F.at(l);
            ARR_F.at(l) = ARR_F.at(r);
            ARR_F.at(r) = f_tmp;
            // swap(P[l], P[r])
            s_tmp = P.at(l);
            P.at(l) = P.at(r);
            P.at(r) = s_tmp;

            l++;
            r--;
        }
        l--;
        // swap(F[l], F[rnd])
        f_tmp = ARR_F.at(l);
        ARR_F.at(l) = ARR_F.at(rnd);
        ARR_F.at(rnd) = f_tmp;
        // swap(P[l], P[rnd])
        s_tmp = P.at(l);
        P.at(l) = P.at(rnd);
        P.at(rnd) = s_tmp;

        sort(left, l - 1);
        sort(r, right);
    }
    void initialization() {
        // number of generation
        g = 1;
        // number of population
        num_NP = NUM_NP_INIT;

        ARR_CR.resize(num_NP);
        ARR_SF.resize(num_NP);
        for (int si = 0; si < num_NP; si++) {
            for (int xi = 0; xi < NUM_X_DIM; xi++)
                P.at(si).at(xi) = x_val_dt(generator);
            ARR_CR.at(si) = NUM_CR_init;
            ARR_F.at(si) = NUM_F_init;
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
    DE(int num_np_init, int num_max_iter, int num_x_dim, int num_x_min, int num_x_max) {
        NUM_MAX_ITER = num_max_iter;
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

        while (g <= NUM_MAX_ITER) {
            // sort(0, num_NP);
            mutation();
            crossover();
            // TODO : Evaluation

            selection();

            // TODO : Parameter update (CR, F)

            // TODO : LPSR

            g++;
        }
    }
};