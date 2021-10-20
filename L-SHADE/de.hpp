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

    /* = = = = = = = = = = =   random objects   = = = = = = = = = = = */
    random_device _rd;
    default_random_engine generator;
    uniform_real_distribution<double> x_distribution;

    Population P, V;

    /* = = = = = = = = = =   L_SHADE functions   = = = = = = = = = = */
    void initialization() {
        printf("num_NP: %d\n", num_NP);
        printf("NUM_X_DIM: %d\n", NUM_X_DIM);

        for (int si = 0; si < this->num_NP; si++) {
            for (int xi = 0; xi < this->NUM_X_DIM; xi++) {
                P.at(si).at(xi) = this->x_distribution(generator);
            }
        }
    }

    // TODO
    // this function sorts both population and fitness array for mutation strategies (pbest) and LPSR (linear population size reduction)
    // the result will sort by fitness (descend)
    void sort() {}

    // TODO
    void mutation() {
        uniform_int_distribution<int> sol_dt(0, num_NP - 1);
        double r1, r2;
    }
    // TODO
    void crossover() {}
    // TODO
    void selection() {}

    // * functions for debugging * //
    void printP() {
        for (auto sol : this->P) {
            for (auto x : sol)
                cout << x << "\t";
            cout << endl;
        }
    }

  public:
    // constructor
    DE(int NUM_NP_INIT, int NUM_MAX_ITER, int NUM_X_DIM, int NUM_X_MIN, int NUM_X_MAX) {
        this->NUM_MAX_ITER = NUM_MAX_ITER;
        this->NUM_X_DIM = NUM_X_DIM;
        this->NUM_X_MIN = NUM_X_MIN;
        this->NUM_X_MAX = NUM_X_MAX;
        this->NUM_NP_INIT = NUM_NP_INIT;
        this->num_NP = NUM_NP_INIT;

        this->P.clear();
        this->V.clear();
        for (int si = 0; si < this->NUM_NP_INIT; si++) {
            this->P.push_back(Solution(NUM_X_DIM, 0));
            this->V.push_back(Solution(NUM_X_DIM, 0));
        }
    }

    // test function
    void test() {
        initialization();
        printP();
    }

    // run L-SHADE algorithm
    double run() {
        /* ======== Initialization ======== */
        // initialize random generator & distribution
        generator.seed(_rd());
        x_distribution.param(uniform_real_distribution<double>(this->NUM_X_MIN, this->NUM_X_MAX).param());

        // number of generation
        int g = 1;
        // number of population
        int num_NP = NUM_NP_INIT;
        // Population
        vector<double> M_CR(num_NP, 0.5), M_F(num_NP, 0.5);

        initialization();
        printP();

        while (g <= NUM_MAX_ITER) {
            for (int si = 0; si < num_NP; si++) {
                /* ======== Parameter update (CR, F) ======== */
                /* ======== Mutation ======== */
                mutation();
                /* ======== Crossover ======== */
                crossover();
                /* ======== Selection ======== */
                selection();
            }
            g++;
        }
    }
};