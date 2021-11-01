#include "cec17_test_func.h"

#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
    random_device rd{};
    mt19937 gen{rd()};

    normal_distribution<> d{0, 0.1};

    for (int n = 0; n < 10000; n++) {
        cout << d(gen) << endl;
    }

    return 0;
}