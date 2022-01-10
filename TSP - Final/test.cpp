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
normal_distribution<double> n_dist{5.0, 1};

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

    for (int i = 0; i < 1000; i++)
        cout << n_dist(mt) << endl;
    return 0;
}