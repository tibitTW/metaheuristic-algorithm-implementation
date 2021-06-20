#include <stdio.h>

#define BIT_SIZE 100
#define ITER_MAX 1000

int Evaluate(int *bitArr) {
    int sum = 0;
    for (int i = 0; i < BIT_SIZE; i++)
        sum += bitArr[i];
    return sum;
}

int UpdateNextAns(int *bitArr) {
    int hold = 1;
    for (int i = BIT_SIZE - 1; i >= 0; i--) {
        if (bitArr[i]) {
            if (hold) {
                bitArr[i] = 0;
            }
        } else {
            if (hold) {
                bitArr[i] = 1;
                hold = 0;
            }
        }
    }
};

int main() {
    int ans[BIT_SIZE] = {0};
    int fitness = Evaluate(ans);
    int bestAns[BIT_SIZE], best_fitness;

    for (int bi = 0; bi < BIT_SIZE; bi++) {
        bestAns[bi] = ans[bi];
    }
    best_fitness = fitness;

    for (int iter = 0; iter < ITER_MAX; iter++) {

        printf("Round %4d, fitness = %3d\n", iter + 1, fitness);

        UpdateNextAns(ans);
        fitness = Evaluate(ans);
        if (fitness > best_fitness) {
            for (int bi = 0; bi < BIT_SIZE; bi++) {
                bestAns[bi] = ans[bi];
            }
            best_fitness = fitness;
        }
    }

    printf("Best fitness : %d\n", best_fitness);
    printf("Best bits :\n[");
    for (int bi = 0; bi < BIT_SIZE; bi++) {
        printf("%d", bestAns[bi]);
    }
    printf("]\n");

    return 0;
}