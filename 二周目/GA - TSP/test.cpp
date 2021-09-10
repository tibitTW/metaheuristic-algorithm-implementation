#include "tsp.h"
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int CITY_DIM = 51;
    vector<vector<int>> city_loc_vec(CITY_DIM, vector<int>(2));
    tsp::loadCityLocation(city_loc_vec, CITY_DIM);
    for (int ci = 0; ci < CITY_DIM; ci++)
        printf("%d %d\n", city_loc_vec[ci][0], city_loc_vec[ci][1]);

    return 0;
}