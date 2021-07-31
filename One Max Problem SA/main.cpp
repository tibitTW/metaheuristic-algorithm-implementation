#include "sa.h"

#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]) {

    srand(time(NULL));
    // read arguments
    if (argc != 10) {
        cout << "Arguemnt count doesn't right." << endl;
        return -1;
    }
    const int ITERATION = atoi(argv[2]), RUN = atoi(argv[3]);
    const double INIT_TEMP = atof(argv[4]), TEMP_COOLDOWN_RATE = atof(argv[5]);
    const bool NB_TYPE = (bool)atoi(argv[6]), F_TYPE = (bool)atoi(argv[7]);
    const int N = atoi(argv[8]);
    const int BIT_SIZE = F_TYPE ? N : atoi(argv[1]);

    char *result_file_path = (char *)malloc(sizeof(char) * strlen(argv[9]));
    strcpy(result_file_path, argv[9]);
    int *result = (int *)malloc(sizeof(int) * (ITERATION + 1)), *sum_of_result = (int *)malloc(sizeof(int) * (ITERATION + 1));

    cout << "================ Experiment arguments ================" << endl;
    cout << "bit size: " << BIT_SIZE << endl;
    cout << "iteration: " << ITERATION << endl;
    cout << "run: " << RUN << endl;
    cout << "initial temperature: " << INIT_TEMP << endl;
    cout << "temperature cooldown rate: " << TEMP_COOLDOWN_RATE << endl;
    cout << "neighbor type: " << NB_TYPE << endl;
    cout << "fitness type: " << F_TYPE << endl;
    cout << "n: " << N << endl;
    cout << "result file path: " << result_file_path << endl << endl;

    for (int ii = 0; ii <= ITERATION; ii++) {
        sum_of_result[ii] = 0;
    }

    FILE *result_file;

    result_file = fopen(result_file_path, "w");

    fprintf(result_file, "Run,");
    for (int r = 0; r <= ITERATION; r++) {
        fprintf(result_file, "%d", r);
        if (r != ITERATION)
            fprintf(result_file, ",");
    }
    fprintf(result_file, "\n");

    for (int r = 1; r <= RUN; r++) {
        SA(BIT_SIZE, ITERATION, INIT_TEMP, TEMP_COOLDOWN_RATE, F_TYPE, NB_TYPE, N, result);

        fprintf(result_file, "%d,", r);
        for (int ii = 0; ii <= ITERATION; ii++) {
            sum_of_result[ii] += result[ii];
            fprintf(result_file, "%d", result[ii]);
            if (ii != ITERATION)
                fprintf(result_file, ",");
        }
        fprintf(result_file, "\n");
    }

    fprintf(result_file, "avg,");
    for (int ii = 0; ii <= ITERATION; ii++) {
        fprintf(result_file, "%lf", (double)sum_of_result[ii] / RUN);
        if (ii != ITERATION)
            fprintf(result_file, ",");
    }
    fprintf(result_file, "\n");

    fclose(result_file);
    return 0;
}