#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

class sa {

    typedef vector<int> result;
    typedef vector<int> solution;

  private:
    int NUM_X_DIM, NUM_MAX_ITER;
    solution s, v;
    int best_f;

    int fitness(solution sol) {
        int f = 0;
        for (int c : sol)
            f += c ? 1 : 0;
        return f;
    }

    solution nb_previous(solution s) {
        solution nb(NUM_X_DIM);
        bool all_zero = true;
        for (int xi = 0; xi < NUM_X_DIM; xi++) {
            if (s.at(xi)) {
                all_zero = false;
                break;
            }
        }
        if (all_zero) {
            for (int xi = 0; xi < NUM_X_DIM; xi++)
                nb.at(xi) = 1;
            return nb;
        }

        int xi = NUM_X_DIM - 1;
        while (!s.at(xi)) {
            nb.at(xi) = 1;
            xi--;
        }
        nb.at(xi) = 0;
        while (xi) {
            nb.at(xi - 1) = s.at(xi - 1);
            xi--;
        }
        return nb;
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
        nb = (rand() % 2) ? nb_previous(s) : nb_next(s);
        return nb;
    }
    void initial(solution &s) {
        int x;
        cout << "initial solution: ";
        for (int xi = 0; xi < NUM_X_DIM; xi++) {
            x = rand() % 2;
            cout << x;
            s.at(xi) = x;
        }
        cout << endl;
    }
    void print_solution(solution s) {
        for (int xi = 0; xi < NUM_X_DIM; xi++)
            cout << s.at(xi);
        cout << endl;
    }

  public:
    sa(int x_dim, int max_iter) {
        NUM_X_DIM = x_dim;
        NUM_MAX_ITER = max_iter;

        srand(time(NULL));
        s.assign(NUM_X_DIM, 0);
    }

    result run() {
        // initialization
        result res(NUM_MAX_ITER);
        initial(s);
        best_f = fitness(s);

        int ii = 0;
        while (ii < NUM_MAX_ITER) {
            v = neighbor(s);

            if (fitness(v) >= fitness(s)) {
                s = v;
                best_f = fitness(v);
            }
            res.at(ii) = best_f;
            ii++;
        }

        return res;
    }
};