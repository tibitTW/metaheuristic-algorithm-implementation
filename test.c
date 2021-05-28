#include <stdio.h>
#include <stdlib.h>

int main() {
    int a;
    for (int i = 0; i < 10000; i++) {
        a = rand() * 2 / RAND_MAX;
        printf("%d ", a);
    }


    return 0;
}
