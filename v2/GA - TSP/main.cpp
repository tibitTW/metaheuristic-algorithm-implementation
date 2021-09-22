#include "config.h"
#include "ga.h"
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    srand(time(NULL));

    // create file to record experiment result
    FILE *result_file;
    result_file = fopen(RESULT_PATH, "w");
    fprintf(result_file, "Run,");
    for (int ii = 0; ii < ITERATION; ii++) {
        fprintf(result_file, "%d", ii + 1);
        if (ii + 1 != ITERATION)
            fprintf(result_file, ",");
    }
    fprintf(result_file, "\n");

    vector<double> result, result_sum(ITERATION, 0);

    tsp::initialize();

    // do ga() for 51 runs, output result
    for (int ri = 0; ri < RUN; ri++) {
        fprintf(result_file, "%d,", ri + 1);
        result = ga::GA();
        for (int ii = 0; ii < ITERATION; ii++) {

            result_sum.at(ii) += result.at(ii);

            fprintf(result_file, "%lf", result.at(ii));
            if (ii + 1 != ITERATION)
                fprintf(result_file, ",");
        }

        fprintf(result_file, "\n");
    }
    fclose(result_file);

    // output result of 51 run avg
    FILE *avg_51_file;
    avg_51_file = fopen(AVG_51_PATH, "w");
    fprintf(avg_51_file, "population: %d\n", POP);
    fprintf(avg_51_file, "crossover rate: %f\n", C_RATE);
    fprintf(avg_51_file, "mutation rate: %f\n\n", M_RATE);
    for (int ii = 0; ii < ITERATION; ii++) {
        fprintf(avg_51_file, "%4d\t%lf\n", ii + 1, result_sum.at(ii) / RUN);
    }
    fclose(avg_51_file);

    return 0;
}