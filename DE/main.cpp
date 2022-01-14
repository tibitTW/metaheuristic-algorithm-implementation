#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "de.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    const int NP = atoi(argv[1]);
    const double CR = atof(argv[2]);
    const double F = atof(argv[3]);
    const int MAX_FES = atoi(argv[4]);
    const int X_DIM = atoi(argv[5]);
    const double X_MIN = atof(argv[6]);
    const double X_MAX = atof(argv[7]);
    const int RUN = atoi(argv[8]);
    de DE(NP, CR, F, MAX_FES, X_DIM, X_MIN, X_MAX);

    double res_sum = 0;
    for (int ri = 0; ri < RUN; ri++) {
        res_sum += DE.run();
    }

    cout << res_sum / RUN << endl;

    return 0;
}