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
    double NUM_CR_init;
    // initial scaling factor rate
    double NUM_F_init;
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

    /* = = = = = = = = = = =   L_SHADE functions   = = = = = = = = = = = */
    void initialization() {
        for (int si = 0; si < this->num_NP; si++) {
            for (int xi = 0; xi < this->NUM_X_DIM; xi++) {
                P.at(si).at(xi) = this->x_distribution(generator);
            }
        }
    }

    // TODO
    void mutation() {}
    // TODO
    void crossover() {}
    // TODO
    void selection() {}

  public:
    // constructor
    DE(double NUM_CR_init, double NUM_F_init, int NUM_NP_INIT, int NUM_MAX_ITER, int NUM_X_DIM, int NUM_X_MIN, int NUM_X_MAX) {
        this->NUM_MAX_ITER = NUM_MAX_ITER;
        this->NUM_X_DIM = NUM_X_DIM;
        this->NUM_X_MIN = NUM_X_MIN;
        this->NUM_X_MAX = NUM_X_MAX;

        this->P.clear();
        this->V.clear();
        for (int si = 0; si < NUM_NP_INIT; si++) {
            this->P.push_back(Solution(NUM_X_DIM, 0));
            this->V.push_back(Solution(NUM_X_DIM, 0));
        }
    }

    // * for test
    void test() {
        generator.seed(_rd());
        x_distribution.param(uniform_real_distribution<double>(this->NUM_X_MIN, this->NUM_X_MAX).param());

        for (int i = 0; i < 100; i++) {
            float x = x_distribution(generator);
            cout << x << endl;
        }
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