#include <stdio.h>

int main() {
    int a = 0, b = 1;
    printf("%d ^ %d : %d\n", a, 0, a^0);
    printf("%d ^ %d : %d\n", a, 1, a^1);
    printf("%d ^ %d : %d\n", b, 0, b^0);
    printf("%d ^ %d : %d\n", b, 1, b^1);

    return 0;
}
