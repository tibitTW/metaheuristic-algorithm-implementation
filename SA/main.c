#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BIT_SIZE 100
#define ITER_MAX 1000
#define DEFAULTE_TEMP 200
#define TEMP_LOWER_BOUND 40
#define TEMP_COLLDOWN_RATE 0.99

int Evaluate(int *bitArr) {
    int sum = 0;
    for (int i = 0; i < BIT_SIZE; i++)
        sum += bitArr[i];
    return sum;
}
double P(int new_sol, int current_sol, double temp) {
    double p = exp((-1) * (new_sol - current_sol) / temp);
    printf("p : %lf\n", p);
    return p;
}

int *PrevOfAns(int *Arr) {
    static int resArr[BIT_SIZE];
    int bi = BIT_SIZE - 1;
    while (!Arr[bi]) {
        resArr[bi] = 1;
        bi--;
    }
    resArr[bi] = 0;
    while (bi) {
        resArr[bi - 1] = Arr[bi - 1];
        bi--;
    }
    return resArr;
}

int *NextOfAns(int *Arr) {
    static int resArr[BIT_SIZE];
    int hold = 1;
    for (int bi = BIT_SIZE - 1; bi >= 0; bi--) {
        resArr[bi] = Arr[bi];
        if (resArr[bi]) {
            if (hold) {
                resArr[bi] = 0;
            }
        } else {
            if (hold) {
                resArr[bi] = 1;
                hold = 0;
            }
        }
    }
    return resArr;
}

int main() {
    srand(time(NULL));
    int Ans[BIT_SIZE];
    for (int bi = 0; bi < BIT_SIZE; bi++) {
        Ans[bi] = (rand() / (float)RAND_MAX) > 0.5;
    }

    int fitness = Evaluate(Ans);
    int best_fitness = fitness;

    int *newAns, accept_new_ans;

    double p, temp = DEFAULTE_TEMP;

    for (int iter = 0; iter < ITER_MAX; iter++) {
        printf("Round %4d, temp = %lf, fitness = %3d\n", iter + 1, temp, fitness);

        if (rand() / (float)RAND_MAX > 0.5) {
            newAns = NextOfAns(Ans);
        } else {
            newAns = PrevOfAns(Ans);
        }

        p = P(Evaluate(newAns), Evaluate(Ans), temp);
        if (p >= 1) {
            accept_new_ans = 1;
        } else {
            accept_new_ans = p > (rand() / (float)RAND_MAX);
        }
        if (accept_new_ans) {
            for (int bi = 0; bi < BIT_SIZE; bi++) {
                Ans[bi] = newAns[bi];
            }
        }

        fitness = Evaluate(Ans);
        best_fitness = best_fitness > fitness ? best_fitness : fitness;

        temp *= TEMP_COLLDOWN_RATE;
        temp = temp > TEMP_LOWER_BOUND ? temp : TEMP_LOWER_BOUND;
    }

    printf("\n--------------------------\n");
    printf("Best fitness : %d\n", best_fitness);

    return 0;
}