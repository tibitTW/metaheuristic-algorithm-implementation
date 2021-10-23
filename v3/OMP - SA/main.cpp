#include "hc.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;
typedef vector<int> result;

void update_sum_result(result &sum_res, result res, int max_iter) {
    for (int xi = 0; xi < max_iter; xi++)
        sum_res.at(xi) += res.at(xi);
}

int main(int argc, char *argv[]) {
    int x_dim = atoi(argv[1]), max_iter = atoi(argv[2]), run = atoi(argv[3]);
    result res, sum_res(max_iter, 0);
    hc HC(x_dim, max_iter);
    for (int r = 0; r < run; r++) {
        res = HC.run();
        update_sum_result(sum_res, res, max_iter);
        for (int ii = 0; ii < max_iter; ii++)
            cout << res.at(ii) << "\t";
        cout << endl;
    }

    fstream file;
    file.open(argv[4], ios::out | ios::trunc);
    for (int ii = 0; ii < max_iter; ii++) {
        file << (double)sum_res.at(ii) / run << "\n";
    }
    file.close();
}