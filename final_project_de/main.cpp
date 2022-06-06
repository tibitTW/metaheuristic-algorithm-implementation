#include <cstdio>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include "de.hpp"
#include "lshade.hpp"
// #include "test_function.hpp"

using namespace std;

typedef vector<double> d1d;

int main(int argc, char *argv[]) {
    string ALGO_TYPE = argv[1];
    int RUN_NUM = atoi(argv[2]);
    int TEST_FUNC_ID = atoi(argv[3]);
    int X_DIM = atoi(argv[4]);
    double X_MIN = atof(argv[5]);
    double X_MAX = atof(argv[6]);

    /* ------------ load parameters ------------ */
    int NP;
    double CR;
    double F;
    int MAX_FES;

    d1d result;

    if (ALGO_TYPE.compare("DE") == 0) { // do de

        /* ------------ load parameters ------------ */

        NP = atoi(argv[7]);
        CR = atof(argv[8]);
        F = atof(argv[9]);
        MAX_FES = atoi(argv[10]);
        /* ----------------------------------------- */

        DE de(NP, CR, F, MAX_FES, X_DIM, X_MIN, X_MAX, TEST_FUNC_ID);
        result = de.run(RUN_NUM);

    } else if (ALGO_TYPE.compare("LSHADE") == 0) { // do l-shade
        LSHADE lshade(X_DIM, X_MIN, X_MAX, TEST_FUNC_ID);
        result = lshade.run(RUN_NUM);
    }

    // * output result
    for (int i = 0; i < result.size(); i++)
        cout << result.at(i) << "\n";

    // * output arguments
    cout << "\n================ arguments ================\n";
    cout << "ALGO_TYPE:      " << ALGO_TYPE << endl;
    cout << "RUN_NUM:        " << RUN_NUM << endl;
    cout << "TEST_FUNC_ID:   " << TEST_FUNC_ID << endl;
    cout << "X_DIM:          " << X_DIM << endl;
    cout << "X_MIN:          " << X_MIN << endl;
    cout << "X_MAX:          " << X_MAX << endl;
    if (ALGO_TYPE.compare("DE") == 0) {
        cout << "NP:             " << NP << endl;
        cout << "CR:             " << CR << endl;
        cout << "F:              " << F << endl;
        cout << "MAX_FES:        " << MAX_FES << endl;
    }

    return 0;
}