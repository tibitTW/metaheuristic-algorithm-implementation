#include "l_shade.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
    const int X_DIM = atoi(argv[1]);
    const double X_MIN = atof(argv[2]);
    const double X_MAX = atof(argv[3]);
    const int FUN_NUM = atoi(argv[4]);
    const int RUN = atoi(argv[5]);

    const int MAX_NFE = X_DIM * 10000;

    char *output_file_path = (char *)malloc(strlen(argv[6]) * sizeof(char));
    strcpy(output_file_path, argv[6]);

    printf("========== Experiment parameters ==========\n");
    printf("x dim:\t%d\n", X_DIM);
    printf("x min:\t%lf\n", X_MIN);
    printf("x max:\t%lf\n", X_MAX);
    printf("function number: %d\n", FUN_NUM);
    printf("x run:\t%d\n", RUN);
    printf("result file path: %s\n", output_file_path);
    cout << endl;

    vector<double> result(RUN, 0);
    DE de(MAX_NFE, X_DIM, X_MIN, X_MAX, FUN_NUM);
    for (int i = 0; i < RUN; i++) {
        result.at(i) = de.run();
    }

    fstream result_file;
    result_file.open(output_file_path, ios::out | ios::trunc);

    for (int i = 0; i < RUN; i++)
        result_file << result.at(i) << endl;

    result_file.close();
}