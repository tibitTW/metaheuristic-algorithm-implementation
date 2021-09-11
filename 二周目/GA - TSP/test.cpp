#include "config.h"
#include "tsp.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

int main() {
    srand(time(NULL));
    vector<int> path;
    for (int ii = 0; ii < 10; ii++) {
        path = tsp::getRandomPath();
        for (int ci : path)
            cout << ci << " ";
        cout << endl;
    }

    return 0;
}