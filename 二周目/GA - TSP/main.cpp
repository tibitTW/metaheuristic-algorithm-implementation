#include "config.h"
#include "ga.h"
#include "tsp.h"
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

    vector<double> result;

    tsp::initialize();

    // do ga() for 51 runs
    for (int ri = 0; ri < RUN; ri++) {
        result = ga::GA();
    }

    return 0;
}