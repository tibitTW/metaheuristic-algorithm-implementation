#include <math.h>
#include <stdio.h>

#include "config.h"

float calculateCityDistance(int x1, int y1, int x2, int y2);

int main() {

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
                    cityRelationMatrix[i][j] = calculate_distance(
                        cityLocation[i][0], cityLocation[i][1],
                        cityLocation[j][0], cityLocation[j][1]);
                }
            }
        }

        for (int i = 0; i < CITY_DIMENSION; i++) {
            for (int j = 0; j < CITY_DIMENSION; j++) {
                printf("%.2f ", cityRelationMatrix[i][j]);
            }
            printf("\n");
        }
    }
    // construct city location to relation matrix END //

    // construct population of ants     //
    {
        int AntsCurrentLocation[POPULATION_SIZE];
        int AntsVisitedCityTable[POPULATION_SIZE][CITY_DIMENSION];
    }
    // construct population of ants end //

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
    // construct pheromone relation matrix end //

    // mainly iteration     //
    for (int iter_count = 0; iter_count < ITERATION_COUNT; iter_count++) {
    }
    // mainly iteration end //

    return 0;
}

float calculateCityDistance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}