#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BIT_SIZE 4
#define ITER_MAX 1000

int Evaluate(int *bitArr) {
    int sum = 0;
    for (int i = 0; i < BIT_SIZE; i++)
        sum += bitArr[i];
    return sum;
}
int UpdatePrevAns(int *Arr, int *prevArr) {
    int bi = BIT_SIZE - 1;
    while (!Arr[bi]) {
        prevArr[bi] = 1;
        bi--;
    }
    prevArr[bi] = 0;
    while (bi) {
        prevArr[bi - 1] = Arr[bi - 1];
        bi--;
    }
}

int UpdateNextAns(int *Arr, int *nextArr) {
    int hold = 1;
    for (int bi = BIT_SIZE - 1; bi >= 0; bi--) {
        nextArr[bi] = Arr[bi];
        if (nextArr[bi]) {
            if (hold) {
                nextArr[bi] = 0;
            }
        } else {
            if (hold) {
                nextArr[bi] = 1;
                hold = 0;
            }
        }
    }
}

int main() {
    srand(time(NULL));
    int Ans[BIT_SIZE];
    for (int bi = 0; bi < BIT_SIZE; bi++) {
        Ans[bi] = (rand() / (float)RAND_MAX) > 0.5;
    }

    int fitness = Evaluate(Ans);
    int best_fitness = fitness;

    int ansPrev[BIT_SIZE], ansNext[BIT_SIZE];
    UpdatePrevAns(Ans, ansPrev);
    UpdateNextAns(Ans, ansNext);

    for (int iter = 0; iter < ITER_MAX; iter++) {
        printf("Round %4d, fitness = %3d\n", iter + 1, fitness);

        if (Evaluate(ansPrev) > Evaluate(ansNext)) {
            // ans = ansPrev
            for (int bi = 0; bi < BIT_SIZE; bi++) {
                Ans[bi] = ansPrev[bi];
            }
        } else {
            // ans = ansNext
            for (int bi = 0; bi < BIT_SIZE; bi++) {
                Ans[bi] = ansNext[bi];
            }
        }
        fitness = Evaluate(Ans);
        best_fitness = best_fitness > fitness ? best_fitness : fitness;

        UpdatePrevAns(Ans, ansPrev);
        UpdateNextAns(Ans, ansNext);
    }

    printf("\n--------------------------\n");
    printf("Best fitness : %d\n", best_fitness);

    return 0;
}