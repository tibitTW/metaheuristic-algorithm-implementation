#include <iomanip>
#include <iostream>
#include <random>

#include "de.hpp"

using namespace std;

int main() {
    // random object
    random_device rd;
    mt19937 generator{rd()};
    uniform_real_distribution<double> unif{0.0, 1.0};
    int NP = 10;
    for (int ii = 0; ii < 1e3; ii++) {
        for (int i = 0; i < NP; i++) {
            int pi = i;
            // generate xr1, xr2, xr3
            int r1 = (int)(unif(generator) * NP) - 1;
            int r2 = (int)(unif(generator) * NP) - 2;
            int r3 = (int)(unif(generator) * NP) - 3;
            r1 += (pi <= r1);
            r2 += (pi <= r2) + (r1 <= r2);
            while (r2 == pi || r2 == r1) {
                r2++;
                r2 = r2 == NP ? 0 : r2;
            }
            r3 += (pi <= r3) + (r1 <= r3) + (r2 <= r3);
            while (r3 == pi || r3 == r1 || r3 == r2) {
                r3++;
                r3 = r3 == NP ? 0 : r3;
            }
        }
    }

    return 0;
}