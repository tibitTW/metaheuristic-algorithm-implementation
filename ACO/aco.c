#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"

double calculateCityDistance(int x1, int y1, int x2, int y2);
double calculateExceptedValue(double tau, double eta);

int main() {
    srand(time(NULL));

    /* TODO : CONSTRUCT CITY LOCATION DATASET TO "CITY DISTANCE RELATION MATRIX" */

    // read file
    FILE *dataset = fopen("./dataset/eil51.txt", "r");

    // check if file exists / can be read
    if (!dataset) {
        printf("Can't read the file. Process end.");
        return 0;
    }

    // convert city location to array "cityLocation"
    int cityLocation[CITY_DIM][2];
    for (int i = 0; i < CITY_DIM; i++) {
        fscanf(dataset, "%*d %d %d", &cityLocation[i][0], &cityLocation[i][1]);
    }

    // relation matrix of city distance
    double cityDistanceRM[CITY_DIM][CITY_DIM];
    // convert array "cityLocation" to relation matrix
    for (int i = 0; i < CITY_DIM; i++) {
        for (int j = 0; j < CITY_DIM; j++) {
            if (i == j) {
                cityDistanceRM[i][j] = 0;
            } else if (i > j) {
                cityDistanceRM[i][j] = cityDistanceRM[j][i];
            } else {
                cityDistanceRM[i][j] =
                    calculateCityDistance(cityLocation[i][0], cityLocation[i][1], cityLocation[j][0], cityLocation[j][1]);
            }
        }
    }

    /* ENDO : CONSTRUCT CITY LOCATION DATASET TO "CITY DISTANCE RELATION MATRIX" */

    /* output relation matrix of city distance for debugging */
    // for (int i = 0; i < CITY_DIM; i++) {
    //     for (int j = 0; j < CITY_DIM; j++) {
    //         printf("%lf\t", cityDistanceRM[i][j]);
    //     }
    //     printf("\n");
    // }

    /* TODO : CONSTRUCT POPULATION ARRAY OF ANTS */

    // record which city this ant current at
    int AntsCurrentCity[ANT_POPULATION];

    // record path length of this ant has passed
    double AntsPathLengthAccumulation[ANT_POPULATION];

    // initizl value is 0, if the value is 1 means this ant has visited the ith city
    int AntsVisitedCity[ANT_POPULATION][CITY_DIM];

    // record the order of cities this ant visited
    int AntsVisitedCityOrder[ANT_POPULATION][CITY_DIM];

    /* ENDO : CONSTRUCT POPULATION ARRAY OF ANTS */

    /* TODO : CONSTRUCT PHEROMONE RELATION MATRIX */
    double PheroRM[CITY_DIM][CITY_DIM];
    // initialize
    for (int i = 0; i < CITY_DIM; i++) {
        for (int j = 0; j < CITY_DIM; j++) {
            if (i == j)
                PheroRM[i][j] = 0;
            else
                PheroRM[i][j] = MIN_PHERO_AMOUNT;
        }
    }
    /* ENDO : CONSTRUCT PHEROMONE RELATION MATRIX */

    /* TODO : CREATE ARRAYS AND VARIABLES FOR REPEATLY USAGE */

    // construct excepted value table
    // |  excepted value  |  probability  |  probability accmulation |
    double exceptedValueTable[CITY_DIM][3];

    /* ENDO : CREATE ARRAYS AND VARIABLES FOR REPEATLY USAGE */

    /* TODO : MAINLY ITERATION */

    for (int iter_count = 0; iter_count < ITERATION_COUNT; iter_count++) {

        /* TODO : INITIALIZE ANTS */

        // reset accumulation array to all zero
        for (int i = 0; i < ANT_POPULATION; i++) {
            AntsPathLengthAccumulation[i] = 0;
        }

        // reset visited city record of ants to all zero
        for (int i = 0; i < ANT_POPULATION; i++) {
            for (int j = 0; j < CITY_DIM; j++) {
                AntsVisitedCity[i][j] = 0;
            }
        }

        // generate a new ant population
        // every ant will place in a random city
        for (int i = 0; i < ANT_POPULATION; i++) {
            AntsCurrentCity[i] = rand() % CITY_DIM;
            AntsVisitedCity[i][AntsCurrentCity[i]] = 1;
            AntsVisitedCityOrder[i][0] = AntsCurrentCity[i];
        }

        /* ENDO : INITIALIZE ANTS */

        /* TODO : LET EVERY ANTS FIND AN COMPLETE PATH */

        for (int ant_i = 0; ant_i < ANT_POPULATION; ant_i++) {
            for (int visited_city_cnt = 1; visited_city_cnt < CITY_DIM; visited_city_cnt++) {

                /* TODO : GENERATE EXCEPTED VALUE TABLE */

                // calculate excepted value of each city
                double sum_of_expected_value = 0, expected_value, sum_of_probability = 0;
                for (int city_idx = 0; city_idx < CITY_DIM; city_idx++) {
                    if (AntsVisitedCity[ant_i][city_idx] == 1) {
                        exceptedValueTable[city_idx][0] = -1;
                    } else {
                        expected_value = calculateExceptedValue(PheroRM[AntsCurrentCity[ant_i]][city_idx],
                                                                1.0 / cityDistanceRM[AntsCurrentCity[ant_i]][city_idx]);
                        exceptedValueTable[city_idx][0] = expected_value;
                        sum_of_expected_value += expected_value;
                    }
                }

                // convert "excepted value" to "probability" and "probability accmulation"
                for (int city_idx = 0; city_idx < CITY_DIM; city_idx++) {
                    if (exceptedValueTable[city_idx][0] == -1) {
                        exceptedValueTable[city_idx][1] = -1;
                        exceptedValueTable[city_idx][2] = -1;
                    } else {
                        exceptedValueTable[city_idx][1] = exceptedValueTable[city_idx][0] / sum_of_expected_value;
                        sum_of_probability += exceptedValueTable[city_idx][1];
                        exceptedValueTable[city_idx][2] = sum_of_probability;
                    }
                }

                /* ENDO : GENERATE EXCEPTED VALUE TABLE */

                /* TODO : PICK NEXT CITY */

                // generate random number
                double rdn = rand() / (float)RAND_MAX;

                // use random number to pick next city
                int next_city_i = 0;
                while (next_city_i < CITY_DIM) {
                    if (exceptedValueTable[next_city_i][2] > rdn) {
                        AntsPathLengthAccumulation[ant_i] += cityDistanceRM[AntsCurrentCity[ant_i]][next_city_i];
                        AntsCurrentCity[ant_i] = next_city_i;
                        AntsVisitedCity[ant_i][next_city_i] = 1;
                        AntsVisitedCityOrder[ant_i][visited_city_cnt] = next_city_i;
                        break;
                    }
                    next_city_i++;
                }

                /* ENDO : PICK NEXT CITY */
            }
        }

        /* ENDO : LET EVERY ANTS FIND AN COMPLETE PATH */

        /* output order of visited city FOR DEBUG */
        //     printf("%d\n", AntsVisitedCityOrder[0][i]);
        // }

        /* TODO : UPDATE PHEROMONE RELATION MATRIX */

        // step1 : reduce
        for (int i = 0; i < CITY_DIM; i++) {
            for (int j = 0; j < CITY_DIM; j++) {
                if (i != j) {
                    PheroRM[i][j] *= (1 - EVAPORATION_FACTOR);
                    PheroRM[i][j] = (PheroRM[i][j] > MIN_PHERO_AMOUNT) ? PheroRM[i][j] : MIN_PHERO_AMOUNT;
                }
            }
        }

        // step2 : addup newly pheromone
        for (int ant_i = 0; ant_i < ANT_POPULATION; ant_i++) {
            double average_pheromone = PHERO_OF_ANT_CARRIED / (double)(CITY_DIM - 1);
            for (int c_i = 0; c_i < CITY_DIM - 1; c_i++) {
                PheroRM[AntsVisitedCityOrder[ant_i][c_i]][AntsVisitedCityOrder[ant_i][c_i + 1]] +=
                    average_pheromone / cityDistanceRM[AntsVisitedCityOrder[ant_i][c_i]][AntsVisitedCityOrder[ant_i][c_i + 1]];
                PheroRM[AntsVisitedCityOrder[ant_i][c_i + 1]][AntsVisitedCityOrder[ant_i][c_i]] =
                    PheroRM[AntsVisitedCityOrder[ant_i][c_i]][AntsVisitedCityOrder[ant_i][c_i + 1]];
            }
        }

        /* output pheromone relation matrix for debugging */
        // for (int c_i = 0; c_i < CITY_DIM; c_i++) {
        //     for (int c_j = 0; c_j < CITY_DIM; c_j++) {
        //         printf("%lf,", PheroRM[c_i][c_j]);
        //     }
        // }
        // printf("\n");

        /* ENDO : UPDATE PHEROMONE RELATION MATRIX */

        /* TODO : UPDATE BEST(SHORTEST) PATH */

        double shortest_path = AntsPathLengthAccumulation[0];
        for (int ant_i = 0; ant_i < ANT_POPULATION; ant_i++) {
            shortest_path = shortest_path < AntsPathLengthAccumulation[ant_i] ? shortest_path : AntsPathLengthAccumulation[ant_i];
        }

        /* output path length of ants for debugging */
        // for (int ant_i = 0; ant_i < ANT_POPULATION; ant_i++) {
        //     printf("%lf", AntsPathLengthAccumulation[ant_i]);
        //     if (ant_i != ANT_POPULATION)
        //         printf(", ");
        // }
        printf("Iteration %2d : Shortest path length : %lf\n", iter_count, shortest_path);
        // printf("----------------------------------------------------\n");

        /* ENDO : UPDATE BEST(SHORTEST) PATH */
    }

    /* ENDO : MAINLY ITERATION */

    return 0;
}

double calculateCityDistance(int x1, int y1, int x2, int y2) { return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); }

double calculateExceptedValue(double tau, double eta) {
    double res = pow(tau, PHERO_CONTROL_FACTOR) * pow(eta, DISTANCE_CONTROL_FACTOR);
    return res;
}