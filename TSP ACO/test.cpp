#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

double getDistance(int x1, int y1, int x2, int y2) {
    int x = abs(x1 - x2), y = abs(y1 - y2);
    double res = sqrt(x * x + y * y);
    return res;
}
int main() {
    int x1 = 0, y1 = 0, x2 = 3, y2 = 4;
    cout << getDistance(x1, y1, x2, y2);
    return 0;
}