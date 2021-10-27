#include "de.hpp"
// #include
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
    vector<int> v1 = {1, 2, 3, 4, 5};
    v1.resize(3);
    for (auto i : v1)
        cout << i << " ";

    // DE de(100, 1000, 10, -30.0, 30.0);
    // de.test();
    // de.run();

    return 0;
}