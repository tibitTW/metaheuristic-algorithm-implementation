#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#define PI acos(-1)

using namespace std;

double ackley2d(vector<double> X, const int X_DIM) {
    double res = 0, a = 20, b = 0.2, c = PI * 2, d = 2;
    res = (-1) * a * exp((-1) * b * sqrt((pow(X[0], 2) + pow(X[1], 2)) / d)) - exp((cos(c * X[0]) + cos(c * X[1])) / d) + a + exp(1);
    return res;
}

double updateVelocity(vector<double> &lastV, vector<double> last_pos, vector<double> Pbest_pos, vector<double> Gbest_pos, const int X_DIM,
                      const int INERTIA_WEIGHT, const int P_LEARNING_FACTOR, const int G_LEARNING_FACTOR, const double V_UPPER_BOUND,
                      const double V_LOWER_BOUND) {
    vector<double> term1(X_DIM), term2(X_DIM), term3(X_DIM);
    for (int xi = 0; xi < X_DIM; xi++) {
        term1[xi] = INERTIA_WEIGHT * lastV[xi];
        term2[xi] = rand() / (float)RAND_MAX * P_LEARNING_FACTOR * (Pbest_pos[xi] - last_pos[xi]);
        term3[xi] = rand() / (float)RAND_MAX * G_LEARNING_FACTOR * (Gbest_pos[xi] - last_pos[xi]);
        lastV[xi] = term1[xi] + term2[xi] + term3[xi];
        lastV[xi] = lastV[xi] > V_UPPER_BOUND ? V_UPPER_BOUND : lastV[xi];
        lastV[xi] = lastV[xi] < V_LOWER_BOUND ? V_LOWER_BOUND : lastV[xi];
    }
}

void pso(const int ITERATION, const double V_LOWER_BOUND, const double V_UPPER_BOUND, const int X_DIM, const int PTC_AMOUNT,
         const double MAP_UPPER_BOUND, const double MAP_LOWER_BOUND, const double INERTIA_WEIGHT, const int P_LEARNING_FACTOR,
         const int G_LEARNING_FACTOR, vector<double> &result) {

    vector<vector<double>> ptcsPos(PTC_AMOUNT, vector<double>(X_DIM));

    // velocity of each particles
    vector<vector<double>> ptcsV(PTC_AMOUNT, vector<double>(X_DIM));

    // best position of each particles visited ever
    vector<vector<double>> ptcsPBestPos(PTC_AMOUNT, vector<double>(X_DIM));

    // best firness ever of each particles
    vector<double> ptcsPBestFitness(PTC_AMOUNT);

    // best position of all particles visited ever
    vector<double> ptcsGBestPos(X_DIM);

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
        ptcsPBestFitness[parti_i] = ackley2d(ptcsPBestPos[parti_i], X_DIM);
    }

    // find global best position and fitness
    int best_i = 0;
    for (int parti_i = 1; parti_i < PTC_AMOUNT; parti_i++) {
        best_i = ptcsPBestFitness[best_i] < ptcsPBestFitness[parti_i] ? best_i : parti_i;
    }
    ptcsGBestFitness = ptcsPBestFitness[best_i];

    for (int iter = 0; iter < ITERATION; iter++) {

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
            updateVelocity(ptcsV[ptc_i], ptcsPos[ptc_i], ptcsPBestPos[ptc_i], ptcsGBestPos, X_DIM, INERTIA_WEIGHT, P_LEARNING_FACTOR,
                           G_LEARNING_FACTOR, V_UPPER_BOUND, V_LOWER_BOUND);
        }

        // calculate fitness, update personal and global best fitness
        double tmp_ack_value;
        int better_checkpoint;
        for (int ptc_i = 0; ptc_i < PTC_AMOUNT; ptc_i++) {
            tmp_ack_value = ackley2d(ptcsPos[ptc_i], X_DIM);
            better_checkpoint = 0;
            if (tmp_ack_value < ptcsPBestFitness[ptc_i]) {
                better_checkpoint = 1; // have chance to challenge global best

                // update personal best position
                for (int xi = 0; xi < X_DIM; xi++) {
                    ptcsPBestPos[ptc_i][xi] = ptcsPos[ptc_i][xi];
                }
                // update personal best fitness
                ptcsPBestFitness[ptc_i] = ackley2d(ptcsPBestPos[ptc_i], X_DIM);
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

        result[iter] = ptcsGBestFitness;
    }
};

int main(int argc, char *argv[]) {
    const int ITERATION = atoi(argv[1]);
    const double V_LOWER_BOUND = atof(argv[2]);
    const double V_UPPER_BOUND = atof(argv[3]);
    const int X_DIM = atoi(argv[4]);
    const int PTC_AMOUNT = atoi(argv[5]);
    const double MAP_LOWER_BOUND = atof(argv[6]);
    const double MAP_UPPER_BOUND = atof(argv[7]);
    const double INERTIA_WEIGHT = atof(argv[8]);
    const int P_LEARNING_FACTOR = atoi(argv[9]);
    const int G_LEARNING_FACTOR = atoi(argv[10]);
    const int RUN = atoi(argv[11]);

    srand(time(NULL));

    vector<vector<double>> ptcsPos(PTC_AMOUNT, vector<double>(X_DIM));

    // velocity of each particles
    vector<vector<double>> ptcsV(PTC_AMOUNT, vector<double>(X_DIM));

    // best position of each particles visited ever
    vector<vector<double>> ptcsPBestPos(PTC_AMOUNT, vector<double>(X_DIM));

    // best firness ever of each particles
    vector<double> ptcsPBestFitness(PTC_AMOUNT);

    // best position of all particles visited ever
    vector<double> ptcsGBestPos(X_DIM);

    // global best fitness
    double ptcsGBestFitness;

    vector<double> result(ITERATION);
    vector<double> result_sum(ITERATION, 0.0);

    fstream output_file;
    output_file.open("result.csv", ios::out | ios::trunc);

    output_file << "Run,";
    for (int i = 0; i < ITERATION; i++) {
        output_file << i;
        if (i != ITERATION - 1)
            output_file << ",";
    }
    output_file << endl;

    for (int ri = 0; ri < RUN; ri++) {
        pso(ITERATION, V_LOWER_BOUND, V_UPPER_BOUND, X_DIM, PTC_AMOUNT, MAP_UPPER_BOUND, MAP_LOWER_BOUND, INERTIA_WEIGHT, P_LEARNING_FACTOR,
            G_LEARNING_FACTOR, result);

        output_file << ri << ",";
        for (int ii = 0; ii < ITERATION; ii++) {
            output_file << result[ii];
            result_sum[ii] += result[ii];
            if (ii != ITERATION - 1)
                output_file << ",";
        }
        output_file << endl;
    }

    output_file << "avg,";
    for (int ii = 0; ii < ITERATION; ii++) {
        output_file << result_sum[ii] / RUN;
        if (ii != ITERATION - 1)
            output_file << ",";
    }
    output_file << endl;

    return 0;
}