#include "cec17_test_func.h"

#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<double> sol1 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double *f;
    cec17_test_func(&sol1.at(0), f, 10, 1, 1);
    cout << *f << endl;

    return 0;
}