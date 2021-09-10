#include "ga.h"
#include "tsp.h"
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    const int CITY_DIM = atoi(argv[1]);
    const int ITERATION = atoi(argv[2]);
    const int POP = atoi(argv[3]);
    const double C_RATE = atof(argv[4]);
    const double M_RATE = atof(argv[5]);
    const int RUN = atoi(argv[6]);

    // do ga() for 51 run
    for (int ri = 0; ri < RUN; ri++) {
        ga::GA(CITY_DIM, ITERATION, POP, C_RATE, M_RATE);
    }

    return 0;
}