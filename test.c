#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main() {
    srand(time(NULL));

    for (int i = 0; i < 100; i++) {
        int point = rand() * 2 / RAND_MAX;
        printf("%d\n", point);
    }


    return 0;
}
