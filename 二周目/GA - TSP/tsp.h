#include "config.h"
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

namespace tsp {

vector<vector<int>> city_loc;
vector<vector<double>> city_dis_RM;

void loadCityLocation(vector<vector<int>> &city_loc) {
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
void loadCityDistanceRM(vector<vector<double>> &city_dis_RM) {
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

double getPathLength(vector<int> path) {
    double path_length = 0;
    int c1, c2;
    for (int i = 0; i < CITY_DIM; i++) {
        c1 = path[i];
        c2 = i + 1 == CITY_DIM ? path[0] : path[i + 1];
        path_length += city_dis_RM[c1][c2];
    }
    return path_length;
}

void initialize() {
    loadCityLocation(city_loc);
    loadCityDistanceRM(city_dis_RM);
}
} // namespace tsp