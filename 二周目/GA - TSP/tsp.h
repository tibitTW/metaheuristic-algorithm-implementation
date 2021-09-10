#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

namespace tsp {

void loadCityLocation(vector<vector<int>> &city_loc, const int CITY_DIM) {
    FILE *city_loc_file;
    city_loc_file = fopen("eil51.txt", "r");
    for (int ci = 0; ci < CITY_DIM; ci++) {
        fscanf(city_loc_file, "%*d %d %d", &city_loc[ci][0], &city_loc[ci][1]);
    }
}
void getPathLength(vector<int> path_order, const int CITY_DIM){};
void initialize(const int CITY_DIM) {}
} // namespace tsp