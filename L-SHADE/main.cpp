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

    bool is_output = argc >= 6;

    char *output_file_path = (char *)malloc(strlen(argv[6]) * sizeof(char));
    strcpy(output_file_path, argv[6]);

    double result[RUN];
    DE de(X_DIM, X_MIN, X_MAX, FUN_NUM);
    for (int i = 0; i < RUN; i++) {
        result[i] = de.run();
    }

    if (is_output) {
        fstream result_file;
        result_file.open(output_file_path, ios::out | ios::trunc);

        for (int i = 0; i < RUN; i++)
            result_file << result[i] << endl;

        result_file.close();
    }

    double sum = 0;

    for (int i = 0; i < RUN; i++)
        sum += result[i];

    sum /= RUN;
    printf("%.2e", sum);

    return 0;
}