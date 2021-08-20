#include "ga.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
    const int BITSIZE = atoi(argv[1]);
    const int ITERATION = atoi(argv[2]);
    const int POPULATION = atoi(argv[3]);
    const double CROSSOVER_P = atof(argv[4]);
    const double MUTATION_P = atof(argv[5]);
    const int RUN = atoi(argv[6]);
    const string result_path(argv[7]);

    fstream result_file;
    result_file.open(result_path, ios::out | ios::trunc);

    result_file << "Run,";
    for (int i = 0; i <= ITERATION; i++) {
        result_file << i;
        if (i != ITERATION)
            result_file << ',';
    }
    result_file << endl;

    vector<int> result, result_accumulation(ITERATION + 1, 0);

    for (int r = 0; r < RUN; r++) {
        result.clear();
        ga::ga(BITSIZE, ITERATION, POPULATION, CROSSOVER_P, MUTATION_P, result);

        result_file << r << ',';
        for (int ii = 0; ii <= ITERATION; ii++) {
            result_accumulation.at(ii) += result.at(ii);
            result_file << result.at(ii);
            if (ii != ITERATION)
                result_file << ',';
        }
        result_file << endl;
    }

    result_file << "avg,";
    for (int ii = 0; ii <= ITERATION; ii++) {
        result_file << (double)result_accumulation.at(ii) / RUN;
        if (ii != ITERATION)
            result_file << ',';
    }
    result_file << endl;

    return 0;
}