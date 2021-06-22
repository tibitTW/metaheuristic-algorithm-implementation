#include <math.h>
#include <stdio.h>

int main() {
    for (double i = -5; i < 5; i += 0.01) {
        printf("exp(%lf) : %lf\n", i, exp(i));
    }

    return 0;
}