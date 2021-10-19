#include "de.hpp"

#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    const int RUN = 51;
    for (int i = 0; i <= RUN; i++) {
        DE::L_SHADE(0.5, 0.5, 100, 1000, 10, -30, 30);
    }
}