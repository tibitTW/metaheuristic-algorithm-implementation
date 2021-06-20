#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PI acos(-1)

#define V_LOWER_BOUND -4
#define V_UPPER_BOUND 4
#define X_DIM 2
#define PTC_AMOUNT 20
#define MAP_UPPER_BOUND 40
#define MAP_LOWER_BOUND -40
#define ITER_COUNT 50
#define INERTIA_WEIGHT 1
#define P_LEARNING_FACTOR 2
#define G_LEARNING_FACTOR 2

double Ackley2d(double *X) {
    double res = 0, a = 20, b = 0.2, c = PI * 2, d = 2;
    res = (-1) * a * exp((-1) * b * sqrt((pow(X[0], 2) + pow(X[1], 2)) / d)) - exp((cos(c * X[0]) + cos(c * X[1])) / d) + a + exp(1);
    return res;
}

double UpdateVelocity(double *lastV, double *lastPos, double *P_best_pos, double *G_best_pos) {
    double term1[X_DIM], term2[X_DIM], term3[X_DIM];
    for (int xi = 0; xi < X_DIM; xi++) {
        term1[xi] = INERTIA_WEIGHT * lastV[xi];
        term2[xi] = rand() / (float)RAND_MAX * P_LEARNING_FACTOR * (P_best_pos[xi] - lastPos[xi]);
        term3[xi] = rand() / (float)RAND_MAX * G_LEARNING_FACTOR * (G_best_pos[xi] - lastPos[xi]);
        lastV[xi] = term1[xi] + term2[xi] + term3[xi];
        lastV[xi] = lastV[xi] > V_UPPER_BOUND ? V_UPPER_BOUND : lastV[xi];
        lastV[xi] = lastV[xi] < V_LOWER_BOUND ? V_LOWER_BOUND : lastV[xi];
    }
}

int main() {
    srand(time(NULL));

    // position of each particles
    double ptcsPos[PTC_AMOUNT][X_DIM];

    // velocity of each particles
    double ptcsV[PTC_AMOUNT][X_DIM];

    // best position of each particles visited ever
    double ptcsPBestPos[PTC_AMOUNT][X_DIM];

    // best firness ever of each particles
    double ptcsPBestFitness[PTC_AMOUNT];

    // best position of all particles visited ever
    double ptcsGBestPos[X_DIM];

    // global best fitness
    double ptcsGBestFitness;

    // initialize random position of all particles
    for (int parti_i = 0; parti_i < PTC_AMOUNT; parti_i++) {
        for (int xi = 0; xi < X_DIM; xi++) {
            ptcsPos[parti_i][xi] = rand() * MAP_UPPER_BOUND * 2 / (double)RAND_MAX - MAP_UPPER_BOUND;
        }
    }

    // initialize random speed of all particles
    for (int parti_i = 0; parti_i < PTC_AMOUNT; parti_i++) {
        for (int xi = 0; xi < X_DIM; xi++) {
            ptcsV[parti_i][xi] = rand() * (V_UPPER_BOUND - V_LOWER_BOUND) / (double)RAND_MAX + V_LOWER_BOUND;
        }
    }

    // set personal first position as personal best position, also calculate personal best fitness
    for (int parti_i = 0; parti_i < PTC_AMOUNT; parti_i++) {
        for (int xi = 0; xi < X_DIM; xi++) {
            ptcsPBestPos[parti_i][xi] = ptcsPos[parti_i][xi];
        }
        ptcsPBestFitness[parti_i] = Ackley2d(ptcsPBestPos[parti_i]);
    }

    // find global best position and fitness
    int best_i = 0;
    for (int parti_i = 1; parti_i < PTC_AMOUNT; parti_i++) {
        best_i = ptcsPBestFitness[best_i] < ptcsPBestFitness[parti_i] ? best_i : parti_i;
    }
    ptcsGBestFitness = ptcsPBestFitness[best_i];

    for (int iter = 0; iter < ITER_COUNT; iter++) {

        // output current position
        printf("Round : %d\n", iter + 1);
        for (int ptc_i = 0; ptc_i < PTC_AMOUNT; ptc_i++) {
            for (int xi = 0; xi < X_DIM; xi++) {
                printf("%lf\t", ptcsPos[ptc_i][xi]);
            }
            printf("\n");
        }
        printf("\n");

        // update new position (notice the map bound)
        for (int ptc_i = 0; ptc_i < PTC_AMOUNT; ptc_i++) {
            for (int xi = 0; xi < X_DIM; xi++) {
                ptcsPos[ptc_i][xi] += ptcsV[ptc_i][xi];
                ptcsPos[ptc_i][xi] = ptcsPos[ptc_i][xi] > MAP_UPPER_BOUND ? MAP_UPPER_BOUND : ptcsPos[ptc_i][xi];
                ptcsPos[ptc_i][xi] = ptcsPos[ptc_i][xi] < MAP_LOWER_BOUND ? MAP_LOWER_BOUND : ptcsPos[ptc_i][xi];
            }
        }

        // update new velocity
        for (int ptc_i = 0; ptc_i < PTC_AMOUNT; ptc_i++) {
            UpdateVelocity(ptcsV[ptc_i], ptcsPos[ptc_i], ptcsPBestPos[ptc_i], ptcsGBestPos);
        }

        // calculate fitness, update personal and global best fitness
        double tmp_ack_value;
        int better_checkpoint;
        for (int ptc_i = 0; ptc_i < PTC_AMOUNT; ptc_i++) {
            tmp_ack_value = Ackley2d(ptcsPos[ptc_i]);
            better_checkpoint = 0;
            if (tmp_ack_value < ptcsPBestFitness[ptc_i]) {
                better_checkpoint = 1; // have chance to challenge global best

                // update personal best position
                for (int xi = 0; xi < X_DIM; xi++) {
                    ptcsPBestPos[ptc_i][xi] = ptcsPos[ptc_i][xi];
                }
                // update personal best fitness
                ptcsPBestFitness[ptc_i] = Ackley2d(ptcsPBestPos[ptc_i]);
            }
            if (better_checkpoint && tmp_ack_value < ptcsGBestFitness) {
                // update global best position
                for (int xi = 0; xi < X_DIM; xi++) {
                    ptcsPBestPos[ptc_i][xi] = ptcsPos[ptc_i][xi];
                }
                // update global best position
                ptcsGBestFitness = tmp_ack_value;
            }
        }
    }

    return 0;
}
