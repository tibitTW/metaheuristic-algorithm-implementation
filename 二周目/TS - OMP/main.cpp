#include "ts.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    // load parameters
    // bitsize iteration run transition_type
    const int BIT_SIZE = atoi(argv[1]), ITERATION = atoi(argv[2]), RUN = atoi(argv[3]), TS_TYPE = atoi(argv[4]);
    char *result_path = (char *)malloc(strlen(argv[5]) * sizeof(char));
    strcpy(result_path, argv[5]);
    int *resultArr = (int *)malloc(sizeof(int) * (ITERATION + 1)), *resultSumArr = (int *)malloc(sizeof(int) * (ITERATION + 1));

    for (int iter = 0; iter <= ITERATION; iter++) {
        resultSumArr[iter] = 0;
    }

    cout << "================ Experiment arguments ================" << endl;
    cout << "bit size: " << BIT_SIZE << endl;
    cout << "iteration: " << ITERATION << endl;
    cout << "run: " << RUN << endl;
    cout << "transition type: " << TS_TYPE << endl;

    fstream result_file;
    result_file.open(result_path, ios::out | ios::trunc);

    result_file << "Run,";

    for (int ii = 0; ii <= ITERATION; ii++) {
        result_file << ii;
        if (ii != ITERATION)
            result_file << ",";
    }
    result_file << endl;

    for (int r = 1; r <= RUN; r++) {
        TS(BIT_SIZE, ITERATION, TS_TYPE, resultArr);

        result_file << r << ",";
        for (int ii = 0; ii <= ITERATION; ii++) {
            resultSumArr[ii] += resultArr[ii];
            result_file << resultArr[ii];
            if (ii != ITERATION)
                result_file << ",";
        }
        result_file << endl;
    }

    result_file << "avg,";
    for (int ii = 0; ii <= ITERATION; ii++) {
        result_file << (double)resultSumArr[ii] / RUN;
        if (ii != ITERATION)
            result_file << ",";
    }
    result_file << endl;

    result_file.close();

    return 0;
}