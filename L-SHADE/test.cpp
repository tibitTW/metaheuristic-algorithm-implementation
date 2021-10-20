#include "de.hpp"

#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
    DE de(100, 1000, 10, -30.0, 30.0);
    de.run();

    return 0;
}