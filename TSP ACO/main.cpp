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

double calculateExceptedValue(double tau, double eta, const int PHERO_CTRL_FACTOR, const int DISTANCE_CTRL_FACTOR) {
    double res = pow(tau, PHERO_CTRL_FACTOR) * pow(eta, DISTANCE_CTRL_FACTOR);
    return res;
}

void aco(const int ITERATION, const int ANT_POP, const int CITY_DIM, const int PHERO_CTRL_FACTOR, const int DISTANCE_CTRL_FACTOR,
         const double EVAPORATION_FACTOR, const double MIN_PHERO_AMOUNT, const double PHERO_ANT_CARRIED, vector<double> ant_path_length_acc,
         vector<int> ants_current_city, vector<vector<int>> ant_visited_city, vector<vector<int>> ants_visited_city_order,
         vector<vector<double>> excepted_value_table, vector<vector<double>> phero_RM, vector<vector<double>> city_distances,
         vector<double> &result) {

    double shortest_path = 10000.0;
    for (int iter = 0; iter < ITERATION; iter++) {

        // reset accumulation array to all zero
        for (int ai = 0; ai < ANT_POP; ai++) {
            ant_path_length_acc[ai] = 0.0;
        }

        // reset ant visited city
        for (int ai = 0; ai < ANT_POP; ai++) {
            for (int ci = 0; ci < CITY_DIM; ci++)
                ant_visited_city[ai][ci] = 0;
        }

        // generate a new ant population
        // every ant will place in a random city
        for (int ai = 0; ai < ANT_POP; ai++) {
            ants_current_city[ai] = rand() % CITY_DIM;
            ant_visited_city[ai][ants_current_city[ai]] = 1;
            ants_visited_city_order[ai][0] = ants_current_city[ai];
        }

        for (int ai = 0; ai < ANT_POP; ai++) {
            for (int city_cnt = 1; city_cnt < CITY_DIM; city_cnt++) {
                double exp_val_sum = 0, exp_val, p_sum = 0;
                // calculate excepted value of each city
                for (int ci = 0; ci < CITY_DIM; ci++) {
                    if (ant_visited_city[ai][ci] == 1) {
                        excepted_value_table[ci][0] = -1;
                    } else {
                        exp_val =
                            calculateExceptedValue(phero_RM[ants_current_city[ai]][ci], 1.0 / city_distances[ants_current_city[ai]][ci],
                                                   PHERO_CTRL_FACTOR, DISTANCE_CTRL_FACTOR);
                        excepted_value_table[ci][0] = exp_val;
                        exp_val_sum += exp_val;
                    }
                }

                // convert "excepted value" to "probability" and "probability accmulation"
                for (int ci = 0; ci < CITY_DIM; ci++) {
                    if (excepted_value_table[ci][0] == -1) {
                        excepted_value_table[ci][1] = -1;
                        excepted_value_table[ci][2] = -1;
                    } else {
                        excepted_value_table[ci][1] = excepted_value_table[ci][0] / exp_val_sum;
                        p_sum += excepted_value_table[ci][1];
                        excepted_value_table[ci][2] = p_sum;
                    }
                }

                // generate random number
                double rdn = rand() / (float)RAND_MAX;

                // use random number to pick next city
                int next_ci = 0;
                while (next_ci < CITY_DIM) {
                    if (excepted_value_table[next_ci][2] > rdn) {

                        ant_path_length_acc[ai] += city_distances[ants_current_city[ai]][next_ci];
                        ants_current_city[ai] = next_ci;
                        ant_visited_city[ai][next_ci] = 1;
                        ants_visited_city_order[ai][city_cnt] = next_ci;
                        break;
                    }

                    next_ci++;
                }
            }

            ant_path_length_acc[ai] += city_distances[ants_current_city[CITY_DIM - 1]][0];
        }

        /* update pheromone relation matrix */

        // 1. reduce
        for (int ci = 0; ci < CITY_DIM; ci++) {
            for (int cj = 0; cj < CITY_DIM; cj++) {
                if (ci != cj) {
                    phero_RM[ci][cj] += (1 - EVAPORATION_FACTOR);
                    phero_RM[ci][cj] = (phero_RM[ci][cj] > MIN_PHERO_AMOUNT) ? phero_RM[ci][cj] : MIN_PHERO_AMOUNT;
                }
            }
        }

        // 2. addup newly pheromone
        for (int ai = 0; ai < ANT_POP; ai++) {
            double avg_phero = (double)PHERO_ANT_CARRIED / CITY_DIM;
            for (int ci = 0; ci < CITY_DIM - 1; ci++) {
                phero_RM[ants_visited_city_order[ai][ci]][ants_visited_city_order[ai][ci + 1]] +=
                    avg_phero / city_distances[ants_visited_city_order[ai][ci]][ants_visited_city_order[ai][ci + 1]];
                phero_RM[ants_visited_city_order[ai][ci + 1]][ants_visited_city_order[ai][ci]] =
                    phero_RM[ants_visited_city_order[ai][ci]][ants_visited_city_order[ai][ci + 1]];
            }
            phero_RM[ants_visited_city_order[ai][CITY_DIM - 1]][ants_visited_city_order[ai][0]] +=
                avg_phero / city_distances[ants_visited_city_order[ai][CITY_DIM - 1]][ants_visited_city_order[ai][0]];
            phero_RM[ants_visited_city_order[ai][CITY_DIM - 1]][ants_visited_city_order[ai][0]] =
                phero_RM[ants_visited_city_order[ai][0]][ants_visited_city_order[ai][CITY_DIM - 1]];
        }

        // update best(shortest) path
        for (int ai = 0; ai < ANT_POP; ai++) {
            shortest_path = shortest_path < ant_path_length_acc[ai] ? shortest_path : ant_path_length_acc[ai];
        }

        // DEBUG: for test
        for (int ai = 0; ai < ANT_POP; ai++) {
            if (ant_path_length_acc[ai] < 426) {
                cout << "total length: " << ant_path_length_acc[ai] << endl;
                for (int ci = 0; ci < CITY_DIM; ci++) {
                    cout << ants_visited_city_order[ai][ci] << endl;
                }
                cout << endl;
            }
        }

        result[iter] = shortest_path;
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

    vector<double> result(ITERATION);
    vector<double> result_sum(ITERATION, 0.0);

    fstream output_file;
    output_file.open("result.csv", ios::out | ios::trunc);

    // output csv heading
    output_file << "Run,";
    for (int iter = 1; iter <= ITERATION; iter++) {
        output_file << iter;
        if (iter != ITERATION)
            output_file << ",";
    }
    output_file << endl;

    for (int r = 0; r < RUN; r++) {
        aco(ITERATION, ANT_POP, CITY_DIM, PHERO_CTRL_FACTOR, DISTANCE_CTRL_FACTOR, EVAPORATION_FACTOR, MIN_PHERO_AMOUNT, PHERO_ANT_CARRIED,
            ant_path_length_acc, ants_current_city, ant_visited_city, ants_visited_city_order, excepted_value_table, phero_RM,
            city_distances, result);

        output_file << r << ",";
        for (int iter = 0; iter < ITERATION; iter++) {
            result_sum[iter] += result[iter];

            output_file << result[iter];
            if (iter != ITERATION - 1)
                output_file << ",";
        }
        output_file << endl;
    }

    output_file << "Avg,";
    for (int iter = 0; iter < ITERATION; iter++) {
        output_file << result_sum[iter] / RUN;
        if (iter != ITERATION - 1)
            output_file << ",";
    }
    output_file << endl;

    output_file.close();
    loc_file.close();

    return 0;
}