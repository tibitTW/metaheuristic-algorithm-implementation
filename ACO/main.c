#include <math.h>
#include <stdio.h>

#define CITY_DIMENSION 51

float calculate_distance(int x1, int y1, int x2, int y2);

int main() {
    FILE *dataset = fopen("./dataset/eil51.txt", "r");

    if (!dataset) {
        printf("Can't read the file.");
        return 0;
    }

    // read city location to cityLocation array
    int cityLocation[CITY_DIMENSION][2];
    for (int i = 0; i < CITY_DIMENSION; i++) {
        fscanf(dataset, "%*d %d %d", &cityLocation[i][0], &cityLocation[i][1]);
    }
    float cityRelationMatrix[CITY_DIMENSION][CITY_DIMENSION];
    for (int i = 0; i < CITY_DIMENSION; i++) {
        for (int j = 0; j < CITY_DIMENSION; j++) {
            if (i == j) {
                cityRelationMatrix[i][j] = 0;
            } else if (i > j) {
                cityRelationMatrix[i][j] = cityRelationMatrix[j][i];
            } else {
                cityRelationMatrix[i][j] =
                    calculate_distance(cityLocation[i][0], cityLocation[i][1],
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

    return 0;
}

float calculate_distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}