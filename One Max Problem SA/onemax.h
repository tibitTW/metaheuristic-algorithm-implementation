#include <math.h>
#include <stdlib.h>

int initSolution(bool *sol, const int BIT_SIZE) {
    for (int bi = 0; bi < BIT_SIZE; bi++) {
        sol[bi] = rand() % 2;
    }
}
int onemaxFitness(bool *sol, const int BIT_SIZE) {
    int res = 0;
    for (int bi = 0; bi < BIT_SIZE; bi++)
        res += sol[bi] != 0 ? 1 : 0;
    return res;
}
int B2D(bool *sol, const int BIT_SIZE) {
    int res = 0;
    for (int bi = 0; bi < BIT_SIZE; bi++) {
        res *= 2;
        res += sol[bi];
    }
    return res;
}
int deceptionFitness(bool *sol, const int BIT_SIZE, const int N) { return abs(B2D(sol, BIT_SIZE) - (int)pow(2, (N - 2))); }

void updateNeighborSolution(bool *nbsol, bool *sol, const int BIT_SIZE, bool nbtype, bool nb_direction) {
    // nbtype => 0: binary numeric, 1: flip one bit
    if (nbtype == 0) {
        // nb_direction => 0: go back, 1: go next
        if (nb_direction == 0) {
            bool all_zero = true;
            for (int bi = 0; bi < BIT_SIZE; bi++) {
                if (sol[bi]) {
                    all_zero = false;
                    break;
                }
            }
            if (all_zero) {
                for (int bi = 0; bi < BIT_SIZE; bi++) {
                    nbsol[bi] = 1;
                }
                return;
            }

            int bi = BIT_SIZE - 1;
            while (!sol[bi]) {
                nbsol[bi] = 1;
                bi--;
            }
            nbsol[bi] = 0;
            while (bi) {
                nbsol[bi - 1] = sol[bi - 1];
                bi--;
            }
            return;
        } else {
            int hold = 1;
            for (int bi = BIT_SIZE - 1; bi >= 0; bi--) {
                nbsol[bi] = sol[bi];
                if (nbsol[bi] && hold) {
                    nbsol[bi] = 0;
                } else if (!nbsol[bi] && hold) {
                    nbsol[bi] = 1;
                    hold = 0;
                }
            }
            return;
        }

    } else if (nbtype == 1) {
        for (int bi = 0; bi < BIT_SIZE; bi++)
            nbsol[bi] = sol[bi];
        int flag = rand() % BIT_SIZE;
        nbsol[flag] = nbsol[flag] ? 0 : 1;
        return;
    }
}

void solcpy(bool *sol, bool *sol_src, const int BIT_SIZE) {
    for (int bi = 0; bi < BIT_SIZE; bi++)
        sol[bi] = sol_src[bi];
}