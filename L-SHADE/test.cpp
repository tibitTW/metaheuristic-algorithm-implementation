#include "cec17_test_func.h"

#include "de.hpp"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
    vector<double> v1 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double f;
    cec17_test_func(&v1[0], &f, 10, 1, 1);
    cout << f << endl;

    return 0;
}