#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

namespace tsp {

vector<vector<int>> city_loc;
vector<vector<double>> city_dis_RM;

void loadCityLocation(vector<vector<int>> &city_loc, const int CITY_DIM) {
    city_loc.clear();
    FILE *city_loc_file;
    city_loc_file = fopen("eil51.txt", "r");
    int cx, cy;
    for (int ci = 0; ci < CITY_DIM; ci++) {
        fscanf(city_loc_file, "%*d %d %d", &cx, &cy);
        city_loc.push_back(vector<int>{cx, cy});
    }
}
double getCityDistance(int cx1, int cy1, int cx2, int cy2) {
    int cx_dis = cx1 - cx2, cy_dis = cy1 - cy2;
    return sqrt(pow(cx_dis, 2) + pow(cy_dis, 2));
}
void loadCityDistanceRM(vector<vector<double>> &city_dis_RM, const int CITY_DIM) {
    city_dis_RM.clear();
    vector<double> rm_row;
    int cx1, cy1, cx2, cy2;
    for (int ci = 0; ci < CITY_DIM; ci++) {
        rm_row.clear();
        for (int cj = 0; cj < CITY_DIM; cj++) {
            if (ci == cj)
                rm_row.push_back(0);
            else {
                cx1 = city_loc.at(ci)[0];
                cy1 = city_loc.at(ci)[1];
                cx2 = city_loc.at(cj)[0];
                cy2 = city_loc.at(cj)[1];
                rm_row.push_back(getCityDistance(cx1, cy1, cx2, cy2));
            }
        }
        city_dis_RM.push_back(rm_row);
    }
}

void initialize(const int CITY_DIM) {
    loadCityLocation(city_loc, CITY_DIM);
    loadCityDistanceRM(city_dis_RM, CITY_DIM);
}
} // namespace tsp