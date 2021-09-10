#include "tsp.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main() {
    tsp::initialize(51);
    for (int ci = 0; ci < 51; ci++) {
        for (int cj = 0; cj < 51; cj++)
            cout << tsp::city_dis_RM[ci][cj] << " ";
        cout << endl;
    }

    return 0;
}