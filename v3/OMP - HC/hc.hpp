#include <bitset>
#include <cstdio>
#include <random>
#include <vector>

using namespace std;
class hc {
    typedef vector<int> result;
    typedef vector<int> solution;

  private:
    int NUM_X_DIM, NUM_MAX_ITER;
    solution s, v;
    int f, best_f;

    random_device rd;
    default_random_engine generator;
    uniform_int_distribution<int> b_dt;

    int fitness(solution sol) {
        int f = 0;
        for (int c : sol)
            f += c ? 1 : 0;
        return f;
    }

    solution nb_previous(solution s) {
        solution nb(NUM_X_DIM);
        ;
        ;
    }
    solution nb_next(solution s) {
        solution nb(NUM_X_DIM);
        int hold = 1;
        for (int xi = NUM_X_DIM - 1; xi >= 0; xi--) {
            nb.at(xi) = (s.at(xi) == hold) ? 0 : 1;
            hold = (s.at(xi) && hold) ? 1 : 0;
        }
        return nb;
    }
    solution neighbor(solution s) {
        solution nb;
        nb = rand() ? nb_previous(s) : nb_next(s);
        return nb;
    }

  public:
    hc(int x_dim, int max_iter) {
        NUM_X_DIM = x_dim;
        NUM_MAX_ITER = max_iter;
        s.assign(NUM_X_DIM, 0);
        s.assign(NUM_X_DIM, 0);
    }

    result run() {

        // initialization
        result res(NUM_MAX_ITER, 1);
        int ii = 0;
        b_dt.param(uniform_int_distribution<int>(0, 1).param());

        while (ii < NUM_MAX_ITER) {
            v = neighbor(s);
            if (fitness(v) >= fitness(s)) {
                s = v;
                best_f = fitness(v);
            }
            res.at(ii) = best_f;
        }

        return res;
    }
};