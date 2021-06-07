#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"

double calculateCityDistance(int x1, int y1, int x2, int y2);

int main() {
    srand(time(NULL));

    // construct city location to relation matrix     //
    {
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
            fscanf(dataset, "%*d %d %d", &cityLocation[i][0],
                   &cityLocation[i][1]);
        }

        // convert array "cityLocation" to relation matrix
        float cityRelationMatrix[CITY_DIMENSION][CITY_DIMENSION];
        for (int i = 0; i < CITY_DIMENSION; i++) {
            for (int j = 0; j < CITY_DIMENSION; j++) {
                if (i == j) {
                    cityRelationMatrix[i][j] = 0;
                } else if (i > j) {
                    cityRelationMatrix[i][j] = cityRelationMatrix[j][i];
                } else {
                    cityRelationMatrix[i][j] = calculateCityDistance(
                        cityLocation[i][0], cityLocation[i][1],
                        cityLocation[j][0], cityLocation[j][1]);
                }
            }
        }
    }
    // construct city location to relation matrix END //

    // construct population of ants     //
    // AntsCurrentCity : record which city this ant current at
    // AntsPathLengthAccumulation : record path length of this ant has passed
    // AntsVisitedCity : value is 0 -> this ant havn't visit the city yet, else
    // the value is 1
    int AntsCurrentCity[POPULATION_SIZE],
        AntsPathLengthAccumulation[POPULATION_SIZE],
        AntsVisitedCity[POPULATION_SIZE][CITY_DIMENSION];
    // construct population of ants END //

    // construct pheromone relation matrix     //
    {
        int PheromoneRelationMatrix[CITY_DIMENSION][CITY_DIMENSION];
        // initialize
        for (int i = 0; i < CITY_DIMENSION; i++) {
            for (int j = 0; j < CITY_DIMENSION; j++) {
                if (i == j)
                    PheromoneRelationMatrix[i][j] = 0;
                else
                    PheromoneRelationMatrix[i][j] = MIN_PHEROMONE_AMOUNT;
            }
        }
    }
    // construct pheromone relation matrix END //

    // create arrays and variables for repeatly usage     //
    // construct excepted value table
    // column:: |  excepted value  |  probability  |  probability accmulation |
    int exceptedValueTable[CITY_DIMENSION][3];

    // create arrays and variables for repeatly usage end //

    // mainly iteration     //
    for (int iter_count = 0; iter_count < ITERATION_COUNT; iter_count++) {

        // initialize ants     //
        {
            // reset accumulation array
            for (int i = 0; i < POPULATION_SIZE; i++)
                AntsPathLengthAccumulation[i] = 0;

            // reset visited city record of ants
            for (int i = 0; i < POPULATION_SIZE; i++) {
                for (int j = 0; j < CITY_DIMENSION; j++) {
                    AntsVisitedCity[i][j] = 0;
                }
            }

            // generate a new ant population
            // every ant will place in a random city
            for (int i = 0; i < POPULATION_SIZE; i++) {
                AntsCurrentCity[i] = rand() % CITY_DIMENSION;
            }
        }
        // initialize ants END //

        // let ants find an complete path
        for (int ant_i = 0; ant_i < POPULATION_SIZE; ant_i++) {
            for (int city_cnt = 1; city_cnt < CITY_DIMENSION; city_cnt++) {
                // calculate τ_ij ^ α * η_ij ^ β
            }
        }

        // update pheromone relation matrix     //

        NULL;

        // update pheromone relation matrix end //

        // update best(shortest) path     //

        NULL;

        // update best(shortest) path end //
    }
    // mainly iteration END //

    return 0;
}

double calculateCityDistance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}