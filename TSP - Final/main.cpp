#include "aco.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<double> d1d;

int main(int argc, char *argv[]) {
    const int RUN = atoi(argv[1]);
    const int CITY_DIM = atoi(argv[2]);
    const int ANT_POP = atoi(argv[3]);
    const int MAX_ITER = atoi(argv[4]);
    const double PHERO_ANT_CARRIED = atof(argv[5]);
    const int PHERO_CTRL_FACTOR = atoi(argv[6]);
    const int DIST_CTRL_FACTOR = atoi(argv[7]);
    const double EVAPORATION_FACTOR = atof(argv[8]);
    const double MIN_PHERO_AMOUNT = atof(argv[9]);
    const int NUM_2OPT_AMOUNT = atoi(argv[10]);
    const double NUM_PBEST = atof(argv[11]);

    cout << "RUN: " << RUN << endl;
    cout << "CITY_DIM: " << CITY_DIM << endl;
    cout << "ANT_POP: " << ANT_POP << endl;
    cout << "MAX_ITER: " << MAX_ITER << endl;
    cout << "PHERO_ANT_CARRIED: " << PHERO_ANT_CARRIED << endl;
    cout << "PHERO_CTRL_FACTOR: " << PHERO_CTRL_FACTOR << endl;
    cout << "DIST_CTRL_FACTOR: " << DIST_CTRL_FACTOR << endl;
    cout << "EVAPORATION_FACTOR: " << EVAPORATION_FACTOR << endl;
    cout << "MIN_PHERO_AMOUNT: " << MIN_PHERO_AMOUNT << endl;
    cout << "NUM_2OPT_AMOUNT: " << NUM_2OPT_AMOUNT << endl;
    cout << "==================\n";

    aco ACO(CITY_DIM, ANT_POP, MAX_ITER, PHERO_ANT_CARRIED, PHERO_CTRL_FACTOR, DIST_CTRL_FACTOR,
            EVAPORATION_FACTOR, MIN_PHERO_AMOUNT, NUM_2OPT_AMOUNT, NUM_PBEST);

    vector<d1d> result_val(RUN, d1d(MAX_ITER));

    for (int ri = 0; ri < RUN; ri++) {
        result_val.at(ri) = ACO.run();
    }

    // output result
    double sum_tmp;
    for (int i = 0; i < MAX_ITER; i++) {
        sum_tmp = 0;
        for (int ri = 0; ri < RUN; ri++)
            sum_tmp += result_val.at(ri).at(i);
        cout << setw(4) << i + 1 << ": " << setprecision(6) << sum_tmp / (double)RUN << endl;
    }

    return 0;
}
