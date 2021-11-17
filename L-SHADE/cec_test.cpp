#include "cec14_test_func.hpp"
// #include "cec17_test_func.h"

#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<double> sol1(10, 0.0);
    double f[10];
    cec14_test_func(&sol1.at(0), f, 10, 1, 1);
    cout << f[0] << endl;

    return 0;
}