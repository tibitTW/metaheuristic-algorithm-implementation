#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"

double calculateCityDistance(int x1, int y1, int x2, int y2);
double calculateExceptedValue(double tau, double eta);
double updateExceptedValueTable();

int main() {
    srand(time(NULL));

    /* TODO : CONSTRUCT CITY LOCATION DATASET TO "CITY DISTANCE RELATION MATRIX" */

    // read file
    FILE *dataset = fopen("./dataset/eil51.txt", "r");

    // check if file exists / can be read
    if (!dataset) {
        printf("Can't read the file.");
        return 0;
    }

    // convert city location to array "cityLocation"
    int cityLocation[CITY_DIMENSION][2];
    for (int i = 0; i < CITY_DIMENSION; i++) {
        fscanf(dataset, "%*d %d %d", &cityLocation[i][0], &cityLocation[i][1]);
    }

    // convert array "cityLocation" to relation matrix
    double cityDistanceRelationMatrix[CITY_DIMENSION][CITY_DIMENSION];
    for (int i = 0; i < CITY_DIMENSION; i++) {
        for (int j = 0; j < CITY_DIMENSION; j++) {
            if (i == j) {
                cityDistanceRelationMatrix[i][j] = 0;
            } else if (i > j) {
                cityDistanceRelationMatrix[i][j] = cityDistanceRelationMatrix[j][i];
            } else {
                cityDistanceRelationMatrix[i][j] =
                    calculateCityDistance(cityLocation[i][0], cityLocation[i][1], cityLocation[j][0], cityLocation[j][1]);
            }
        }
    }

    /* ENDO : CONSTRUCT CITY LOCATION DATASET TO "CITY DISTANCE RELATION MATRIX" */

    /* TODO : CONSTRUCT POPULATION ARRAY OF ANTS */

    // "AntsCurrentCity" : record which city this ant current at
    // "AntsPathLengthAccumulation" : record path length of this ant has passed
    // "AntsVisitedCity" : initizl value is 0, if the value is 1 means this ant has visited the ith city
    int AntsCurrentCity[POPULATION_SIZE], AntsPathLengthAccumulation[POPULATION_SIZE], AntsVisitedCity[POPULATION_SIZE][CITY_DIMENSION],
        AntsVisitedCityOrder[POPULATION_SIZE][CITY_DIMENSION];

    /* ENDO : CONSTRUCT POPULATION ARRAY OF ANTS */

    /* TODO : CONSTRUCT PHEROMONE RELATION MATRIX */
    double PheromoneRelationMatrix[CITY_DIMENSION][CITY_DIMENSION];
    // initialize
    for (int i = 0; i < CITY_DIMENSION; i++) {
        for (int j = 0; j < CITY_DIMENSION; j++) {
            if (i == j)
                PheromoneRelationMatrix[i][j] = 0;
            else
                PheromoneRelationMatrix[i][j] = MIN_PHEROMONE_AMOUNT;
        }
    }
    /* ENDO : CONSTRUCT PHEROMONE RELATION MATRIX */

    /* TODO : CREATE ARRAYS AND VARIABLES FOR REPEATLY USAGE */

    // construct excepted value table
    // column:: |  excepted value  |  probability  |  probability accmulation |
    double exceptedValueTable[CITY_DIMENSION][3];

    /* ENDO : CREATE ARRAYS AND VARIABLES FOR REPEATLY USAGE */

    /* TODO : MAINLY ITERATION */

    for (int iter_count = 0; iter_count < ITERATION_COUNT; iter_count++) {

        /* TODO : INITIALIZE ANTS */

        // reset accumulation array to all zero
        for (int i = 0; i < POPULATION_SIZE; i++) {
            AntsPathLengthAccumulation[i] = 0;
        }

        // reset visited city record of ants to all zero
        for (int i = 0; i < POPULATION_SIZE; i++) {
            for (int j = 0; j < CITY_DIMENSION; j++) {
                AntsVisitedCity[i][j] = 0;
            }
        }

        // generate a new ant population
        // every ant will place in a random city
        for (int i = 0; i < POPULATION_SIZE; i++) {
            AntsCurrentCity[i] = rand() % CITY_DIMENSION;
            AntsVisitedCity[i][AntsCurrentCity[i]] = 1;
            AntsVisitedCityOrder[i][0] = AntsCurrentCity[i];
        }

        /* ENDO : INITIALIZE ANTS */

        /* TODO : LET EVERY ANTS FIND AN COMPLETE PATH */

        for (int ant_i = 0; ant_i < POPULATION_SIZE; ant_i++) {
            for (int visited_city_cnt = 1; visited_city_cnt < CITY_DIMENSION; visited_city_cnt++) {

                /* TODO : GENERATE EXCEPTED VALUE TABLE */

                // calculate excepted value of each city
                double sum_of_expected_value = 0, expected_value, sum_of_probability = 0;
                for (int city_idx = 0; city_idx < CITY_DIMENSION; city_idx++) {
                    if (AntsVisitedCity[ant_i][city_idx] == 1) {
                        exceptedValueTable[city_idx][0] = -1;
                    } else {
                        expected_value = calculateExceptedValue(PheromoneRelationMatrix[AntsCurrentCity[ant_i]][city_idx],
                                                                1 / cityDistanceRelationMatrix[ant_i][city_idx]);
                        exceptedValueTable[city_idx][0] = expected_value;
                        sum_of_expected_value += expected_value;
                    }
                }
                // convert "excepted value" to "probability" and "probability accmulation"
                for (int city_idx = 0; city_idx < CITY_DIMENSION; city_idx++) {
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
                float rdn = rand() / (float)RAND_MAX;
                int next_city_i = 0;
                while (next_city_i < CITY_DIMENSION) {
                    if (exceptedValueTable[next_city_i][2] > rdn) {
                        AntsPathLengthAccumulation[ant_i] += cityDistanceRelationMatrix[AntsCurrentCity[ant_i]][next_city_i];
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

        for (int i = 0; i < CITY_DIMENSION; i++) {
            printf("%d\n", AntsVisitedCityOrder[0][i]);
        }

        /* ENDO : LET EVERY ANTS FIND AN COMPLETE PATH */

        /* TODO : UPDATE PHEROMONE RELATION MATRIX */

        NULL;

        /* ENDO : UPDATE PHEROMONE RELATION MATRIX */

        /* TODO : UPDATE BEST(SHORTEST) PATH */

        NULL;

        /* ENDO : UPDATE BEST(SHORTEST) PATH */
    }

    /* ENDO : MAINLY ITERATION */

    return 0;
}

double calculateCityDistance(int x1, int y1, int x2, int y2) { return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); }

double calculateExceptedValue(double tau, double eta) {
    double res = pow(tau, PHEROMONE_CONTROL_FACTOR) * pow(eta, DISTANCE_CONTROL_FACTOR);
    return res;
}