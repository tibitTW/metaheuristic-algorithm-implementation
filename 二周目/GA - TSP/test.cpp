#include "config.h"
#include "tsp.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

int main() {
    Chromo c1{1, 3, 9, 7, 5, 4, 6, 2, 8}, c2{4, 6, 2, 1, 7, 8, 9, 3, 5};
    CX(c1, c2, 9);
    for (int ci = 0; ci < 9; ci++)
        cout << c1[ci] << " ";
    cout << endl;
    for (int ci = 0; ci < 9; ci++)
        cout << c2[ci] << " ";
    cout << endl;

    return 0;
}