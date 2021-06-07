#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    printf("%f", pow(1.1, 100));
    double a = 1.1;
    for (int i = 0; i < 100; i++) {
        printf("%10.5f ", a);
        a *= 1.1;
        if (i % 5 == 0)
            printf("\n");
    }

    return 0;
}