#include <fstream>
#include <iostream>
#include <math.h>
#include <random>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef vector<int> i1d;
typedef vector<i1d> i2d;
typedef vector<double> d1d;
typedef vector<d1d> d2d;

// random
random_device rd;
mt19937 generator(rd());
uniform_real_distribution<double> unif(0.0, 1.0);

double getDistance(i1d loc1, i1d loc2) {
    int x1 = loc1.at(0), y1 = loc1.at(1);
    int x2 = loc2.at(0), y2 = loc2.at(1);
    int x = abs(x1 - x2), y = abs(y1 - y2);
    return sqrt(x * x + y * y);
}
double getDistance(int x1, int y1, int x2, int y2) {
    int x = abs(x1 - x2), y = abs(y1 - y2);
    double res = sqrt(x * x + y * y);
    return res;
}
void output_result(fstream &output_file, d1d result) {
    for (int i = 0; i < result.size(); i++) {
        output_file << result.at(i);
        if (i != result.size() - 1)
            output_file << ",";
    }
    output_file << endl;
}
void loadLocations(i2d &city_locations, d2d &city_distances, fstream &loc_file, const int CITY_DIM) {
    // load locations from file
    int tmp;
    for (int i = 0; i < CITY_DIM; i++)
        loc_file >> tmp >> city_locations.at(i).at(0) >> city_locations.at(i).at(1);

    for (int i = 0; i < CITY_DIM; i++) {
        city_distances.at(i).at(i) = 0;
        for (int j = i + 1; j < CITY_DIM; j++)
            city_distances.at(j).at(i) = city_distances.at(i).at(j) = getDistance(city_locations.at(i), city_locations.at(j));
    }
}
double calculateExceptedValue(double tau, double eta, const int PHERO_CTRL_FACTOR, const int DISTANCE_CTRL_FACTOR) {
    return pow(tau, PHERO_CTRL_FACTOR) * pow(eta, DISTANCE_CTRL_FACTOR);
}

d1d aco(const int MAX_ITER, const int ANT_POP, const int CITY_DIM, const int PHERO_CTRL_FACTOR, const int DISTANCE_CTRL_FACTOR,
        const double EVAPORATION_FACTOR, const double MIN_PHERO_AMOUNT, const double PHERO_ANT_CARRIED, d2d city_distances) {

    d1d result;
    double shortest_path = 9999.9;

    i1d ants_current_city(ANT_POP);
    d1d ant_path_length_acc(ANT_POP);
    i2d ant_visited_city(ANT_POP, i1d(CITY_DIM));
    i2d ants_visited_city_order(ANT_POP, i1d(CITY_DIM));
    d2d excepted_value_table(CITY_DIM, d1d(3));
    d2d phero_RM(CITY_DIM, d1d(CITY_DIM, MIN_PHERO_AMOUNT));

    for (int iter = 0; iter < MAX_ITER; iter++) {

        // reset accumulation array to all zero
        ant_path_length_acc.assign(ANT_POP, 0.0);

        // reset ant visited city
        for (int ai = 0; ai < ANT_POP; ai++)
            ant_visited_city.at(ai).assign(CITY_DIM, 0);

        // generate a new ant population, every ant will be placeed in a random city
        for (int ai = 0; ai < ANT_POP; ai++) {
            int ri = (int)(unif(generator) * CITY_DIM);
            while (ri == CITY_DIM)
                ri = (int)(unif(generator) * CITY_DIM);
            ants_current_city.at(ai) = ri;
            ant_visited_city.at(ai).at(ri) = 1;
            ants_visited_city_order.at(ai).at(0) = ri;
        }

        for (int ai = 0; ai < ANT_POP; ai++) {
            for (int city_cnt = 1; city_cnt < CITY_DIM; city_cnt++) {
                double exp_val_sum = 0, exp_val, p_sum = 0;
                // calculate excepted value of each city
                for (int ci = 0; ci < CITY_DIM; ci++) {
                    if (ant_visited_city.at(ai).at(ci) == 1) {
                        excepted_value_table.at(ci).at(0) = -1;
                    } else {
                        exp_val = calculateExceptedValue(phero_RM.at(ants_current_city.at(ai)).at(ci),
                                                         1.0 / city_distances.at(ants_current_city.at(ai)).at(ci), PHERO_CTRL_FACTOR,
                                                         DISTANCE_CTRL_FACTOR);
                        excepted_value_table.at(ci).at(0) = exp_val;
                        exp_val_sum += exp_val;
                    }
                }

                // convert "excepted value" to "probability" and "probability accmulation"
                for (int ci = 0; ci < CITY_DIM; ci++) {
                    if (excepted_value_table.at(ci).at(0) == -1) {
                        excepted_value_table.at(ci).at(1) = excepted_value_table.at(ci).at(2) = -1;
                    } else {
                        excepted_value_table.at(ci).at(1) = excepted_value_table.at(ci).at(0) / exp_val_sum;
                        p_sum += excepted_value_table.at(ci).at(1);
                        excepted_value_table.at(ci).at(2) = p_sum;
                    }
                }

                // generate random number
                double rdn = unif(generator);

                // use random number to pick next city
                int next_ci = 0;
                while (next_ci < CITY_DIM) {
                    if (excepted_value_table.at(next_ci).at(2) > rdn) {
                        ant_path_length_acc.at(ai) += city_distances.at(ants_current_city.at(ai)).at(next_ci);
                        ants_current_city.at(ai) = next_ci;
                        ant_visited_city.at(ai).at(next_ci) = 1;
                        ants_visited_city_order.at(ai).at(city_cnt) = next_ci;
                        break;
                    }

                    next_ci++;
                }
            }

            ant_path_length_acc.at(ai) += city_distances.at(ants_current_city.at(CITY_DIM - 1)).at(ants_visited_city_order.at(ai).at(0));
        }

        /* update pheromone relation matrix */

        // 1. reduce
        for (int ci = 0; ci < CITY_DIM; ci++) {
            for (int cj = 0; cj < CITY_DIM; cj++) {
                if (ci != cj) {
                    phero_RM.at(ci).at(cj) *= (1 - EVAPORATION_FACTOR);
                    phero_RM.at(ci).at(cj) = (phero_RM.at(ci).at(cj) > MIN_PHERO_AMOUNT) ? phero_RM.at(ci).at(cj) : MIN_PHERO_AMOUNT;
                }
            }
        }

        // 2. addup newly pheromone
        for (int ai = 0; ai < ANT_POP; ai++) {
            double avg_phero = PHERO_ANT_CARRIED / CITY_DIM;

            int c1, c2;
            for (int ci = 0; ci < CITY_DIM - 1; ci++) {
                c1 = ants_visited_city_order.at(ai).at(ci);
                c2 = ants_visited_city_order.at(ai).at(ci + 1);
                phero_RM.at(c2).at(c1) = phero_RM.at(c1).at(c2) += avg_phero / city_distances.at(c1).at(c2);
            }
            c1 = ants_visited_city_order.at(ai).at(CITY_DIM - 1);
            c2 = ants_visited_city_order.at(ai).at(0);
            phero_RM.at(c2).at(c1) = phero_RM.at(c1).at(c2) += avg_phero / city_distances.at(c1).at(c2);
        }

        // update best(shortest) path
        for (int ai = 0; ai < ANT_POP; ai++) {
            if (shortest_path > ant_path_length_acc.at(ai)) {
                shortest_path = ant_path_length_acc.at(ai);

                cout << "good path:" << endl;
                for (int ci = 0; ci < CITY_DIM; ci++)
                    cout << ants_visited_city_order.at(ai).at(ci) << endl;
                cout << endl;
            }
        }
        result.push_back(shortest_path);
    }

    return result;
}

int main(int argc, char *argv[]) {
    // load arguments
    const int CITY_DIM = atoi(argv[1]);
    const int ANT_POP = atoi(argv[2]);
    const int MAX_ITER = atoi(argv[3]);
    const double PHERO_ANT_CARRIED = atof(argv[4]);
    const int PHERO_CTRL_FACTOR = atoi(argv[5]);
    const int DISTANCE_CTRL_FACTOR = atoi(argv[6]);
    const double EVAPORATION_FACTOR = atof(argv[7]);
    const double MIN_PHERO_AMOUNT = atof(argv[8]);
    const int RUN = atoi(argv[9]);

    cout << "CITY DIM: " << CITY_DIM << endl;
    cout << "ANT POP: " << ANT_POP << endl;
    cout << "MAX ITER: " << MAX_ITER << endl;
    cout << "PHERO ANT CARRIED: " << PHERO_ANT_CARRIED << endl;
    cout << "PHERO CTRL FACTOR: " << PHERO_CTRL_FACTOR << endl;
    cout << "DISTANCE CTRL FACTOR: " << DISTANCE_CTRL_FACTOR << endl;
    cout << "EVAPORATION FACTOR: " << EVAPORATION_FACTOR << endl;
    cout << "MIN PHERO AMOUNT: " << MIN_PHERO_AMOUNT << endl;
    cout << "RUN: " << RUN << endl;

    /* =================== load city locations =================== */

    // stores city locations
    i2d city_locations(CITY_DIM, i1d(2, 0));
    // stores city distances
    d2d city_distances(CITY_DIM, d1d(CITY_DIM, 0));
    // load city location dataset
    fstream loc_file;
    loc_file.open("./eil51.txt", ios::in);
    loadLocations(city_locations, city_distances, loc_file, CITY_DIM);
    loc_file.close();

    fstream ex_detail_file;
    ex_detail_file.open("detail.csv", ios::out | ios::trunc);
    // print csv heading
    ex_detail_file << "Run,";
    for (int iter = 1; iter <= MAX_ITER; iter++) {
        ex_detail_file << iter;
        if (iter != MAX_ITER)
            ex_detail_file << ",";
    }
    ex_detail_file << endl;

    d1d result_sum(MAX_ITER, 0.0);
    d1d result;
    for (int r = 0; r < RUN; r++) {
        result = aco(MAX_ITER, ANT_POP, CITY_DIM, PHERO_CTRL_FACTOR, DISTANCE_CTRL_FACTOR, EVAPORATION_FACTOR, MIN_PHERO_AMOUNT,
                     PHERO_ANT_CARRIED, city_distances);

        ex_detail_file << r + 1 << ",";
        output_result(ex_detail_file, result);

        for (int iter = 0; iter < MAX_ITER; iter++)
            result_sum.at(iter) += result.at(iter);
    }

    for (int iter = 0; iter < MAX_ITER; iter++)
        result_sum.at(iter) /= RUN;
    // print avg
    ex_detail_file << "Avg,";
    output_result(ex_detail_file, result_sum);

    ex_detail_file.close();

    return 0;
}