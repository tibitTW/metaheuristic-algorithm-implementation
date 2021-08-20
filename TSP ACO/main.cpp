#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

double getDistance(vector<int> loc1, vector<int> loc2) {
    int x1 = loc1[0], y1 = loc1[1];
    int x2 = loc2[0], y2 = loc2[1];
    int x = abs(x1 - x2), y = abs(y1 - y2);
    return sqrt(x * x + y * y);
}
double getDistance(int x1, int y1, int x2, int y2) {
    int x = abs(x1 - x2), y = abs(y1 - y2);
    double res = sqrt(x * x + y * y);
    return res;
}

void loadLocations(vector<vector<int>> &city_locations, vector<vector<double>> &city_distances, fstream &loc_file, const int CITY_DIM) {
    // load locations from file
    int tmp;
    for (int i = 0; i < CITY_DIM; i++)
        loc_file >> tmp >> city_locations[i][0] >> city_locations[i][1];

    for (int i = 0; i < CITY_DIM; i++) {
        city_distances[i][i] = 0;
        for (int j = i; j < CITY_DIM; j++) {
            city_distances[i][j] = getDistance(city_locations[i], city_locations[j]);
            city_distances[j][i] = city_distances[i][j];
        }
    }
}

void initPheroRM(vector<vector<double>> &phero_RM, const int CITY_DIM, const double MIN_PHERO_AMOUNT) {
    for (int i = 0; i < CITY_DIM; i++) {
        for (int j = 0; j < CITY_DIM; j++) {
            phero_RM[i][j] = i == j ? 0 : MIN_PHERO_AMOUNT;
        }
    }
}

void aco(const int ITERATION, const int ANT_POP, const int CITY_DIM, vector<int> ant_path_length_acc, vector<int> ants_current_city,
         vector<vector<int>> ant_visited_city, vector<vector<int>> ants_visited_city_order) {
    for (int iter = 0; iter < ITERATION; iter++) {

        // reset accumulation array to all zero
        for (int ai = 0; ai < ANT_POP; ai++) {
            ant_path_length_acc[ai] = 0;
        }

        // generate a new ant population
        // every ant will place in a random city
        for (int ai = 0; ai < ANT_POP; ai++) {
            ants_current_city[ai] = rand() % CITY_DIM;
            ant_visited_city[ai][ants_current_city[ai]] = 1;
            ants_visited_city_order[ai][0] = ants_current_city[ai];
        }
    }
}

int main(int argc, char *argv[]) {
    // load arguments
    const int CITY_DIM = atoi(argv[1]);
    const int ANT_POP = atoi(argv[2]);
    const int ITERATION = atoi(argv[3]);
    const double PHERO_ANT_CARRIED = atof(argv[4]);
    const int PHERO_CTRL_FACTOR = atoi(argv[5]);
    const int DISTANCE_CTRL_FACTOR = atoi(argv[6]);
    const double EVAPORATION_FACTOR = atof(argv[7]);
    const double MIN_PHERO_AMOUNT = atof(argv[8]);
    const int RUN = atoi(argv[9]);

    // load city location dataset
    fstream loc_file;
    loc_file.open("./eil51.txt", ios::in);

    // stores city locations
    vector<vector<int>> city_locations(CITY_DIM, vector<int>(2, 0));
    // stores city distances
    vector<vector<double>> city_distances(CITY_DIM, vector<double>(CITY_DIM, 0));

    loadLocations(city_locations, city_distances, loc_file, CITY_DIM);

    vector<int> ants_current_city(ANT_POP);
    vector<double> ant_path_length_acc(ANT_POP);
    vector<vector<int>> ant_visited_city(ANT_POP, vector<int>(CITY_DIM));
    vector<vector<int>> ants_visited_city_order(ANT_POP, vector<int>(CITY_DIM));

    vector<vector<double>> phero_RM(CITY_DIM, vector<double>(CITY_DIM));
    initPheroRM(phero_RM, CITY_DIM, MIN_PHERO_AMOUNT);

    vector<vector<double>> excepted_value_table(CITY_DIM, vector<double>(3));

    for (int r = 0; r < RUN; r++) {
        aco();
    }
    return 0;
}