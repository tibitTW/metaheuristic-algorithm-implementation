#include "hc.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;
typedef vector<int> result;

void update_sum_result(result sum_res, result res, int x_dim) {
    for (int xi = 0; xi < x_dim; xi++)
        sum_res.at(xi) += res.at(xi);
}

int main(int argc, char *argv[]) {
    int x_dim = atoi(argv[0]), max_iter = atoi(argv[1]), run = atoi(argv[2]);
    result res, sum_res(x_dim, 0);
    hc HC(x_dim, max_iter);
    for (int r = 0; r < run; r++) {
        res = HC.run();
        update_sum_result(sum_res, res, x_dim);
    }

    fstream file;
    file.open(argv[3], ios::out | ios::trunc);
    for (int ii = 0; ii < max_iter; ii++) {
        file << (double)sum_res.at(ii) / run << "\n";
    }
}