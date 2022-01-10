#include "aco.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <vector>

using namespace std;

// random number generator
random_device rd;
mt19937 mt(rd());
uniform_real_distribution<double> dist(0.0, 1.0);

typedef vector<int> i1d;
int main() {
    // int CITY_DIM = 51;
    // int ANT_POP = 10;
    // int MAX_ITER = 10;
    // double PHERO_ANT_CARRIED = 0.5;
    // int PHERO_CTRL_FACTOR = 1;
    // int DIST_CTRL_FACTOR = 1;
    // double EVAPORATION_FACTOR = 0.5;
    // double MIN_PHERO_AMOUNT = 0.5;
    // int RUN = 10;
    // aco aco(CITY_DIM, ANT_POP, MAX_ITER, PHERO_ANT_CARRIED, PHERO_CTRL_FACTOR, DIST_CTRL_FACTOR,
    //         EVAPORATION_FACTOR, MIN_PHERO_AMOUNT);

    i1d v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto i : v1)
        cout << i << " ";
    cout << endl;
    v1.resize(5);
    for (auto i : v1)
        cout << i << " ";
    cout << endl;

    return 0;
}