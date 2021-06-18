#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PI acos(-1)

#define MIN_SPEED -4
#define MAX_SPEED 4
#define X_DIM 2
#define PARTICLE_AMOUNT 1000
#define MAP_BOUND 40

double Ackley2d(double x1, double x2) {
    double res = 0, a = 20, b = 0.2, c = PI * 2, d = 2;
    res = (-1) * a * exp((-1) * b * sqrt((pow(x1, 2) + pow(x2, 2)) / d)) - exp((cos(c * x1) + cos(c * x2)) / d) + a + exp(1);
    return res;
}

int main() {
    srand(time(NULL));

    // records position of each particles
    double particlesPosition[PARTICLE_AMOUNT][X_DIM];

    for (int parti_i = 0; parti_i < PARTICLE_AMOUNT; parti_i++) {
        for (int x_i = 0; x_i < X_DIM; x_i++) {
            particlesPosition[parti_i][x_i] = rand() * MAP_BOUND * 2 / (double)RAND_MAX - MAP_BOUND;
        }
    }

    // records speed of each particles
    double particlesSpeed[PARTICLE_AMOUNT][X_DIM];

    for (int parti_i = 0; parti_i < PARTICLE_AMOUNT; parti_i++) {
        for (int x_i = 0; x_i < X_DIM; x_i++) {
            particlesSpeed[parti_i][x_i] = rand() * (MAX_SPEED - MIN_SPEED) / (double)RAND_MAX + MIN_SPEED;
            printf("%lf\t", particlesSpeed[parti_i][x_i]);
        }
        printf("\n");
    }

    // records best position of each particles visited ever
    double particlesPersonalBestPosition[PARTICLE_AMOUNT][X_DIM];

    for (int parti_i = 0; parti_i < PARTICLE_AMOUNT; parti_i++) {
        for (int x_i = 0; x_i < X_DIM; x_i++) {
            particlesPersonalBestPosition[parti_i][x_i] = particlesPosition[parti_i][x_i];
        }
    }

    // records best position of all particles this round
    double particlesGlobalBest[X_DIM];

    return 0;
}
