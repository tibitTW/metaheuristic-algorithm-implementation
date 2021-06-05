#include <math.h>
#include <stdio.h>

float calculate_distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    int x1 = 1, y1 = 2, x2 = 3, y2 = 4;
    float dis = calculate_distance(x1, y1, x2, y2);
    printf("%f", dis);

    return 0;
}