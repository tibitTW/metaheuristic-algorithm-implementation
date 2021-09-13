#include "config.h"
#include "ga.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

#define CITY_DIM 10

vector<int> getRandomPath() {
    vector<int> num_selected(CITY_DIM, 0), path;
    int flag, si;
    for (int ci = 0; ci < CITY_DIM; ci++) {
        flag = rand() % (CITY_DIM - ci);
        for (int si = 0; si < CITY_DIM; si++) {
            if (!flag && !num_selected[si]) {
                num_selected[si] = 1;
                path.push_back(si);
                break;
            }
            flag -= num_selected[si] ? 0 : 1;
        }
    }

    return path;
}
int main() {
    srand(time(NULL));

    vector<int> vec;

    for (int i = 0; i < 10; i++) {
        vec = getRandomPath();
        for (int ii = 0; ii < 10; ii++)
            cout << vec[ii] << " ";
        cout << endl;
    }

    return 0;
}