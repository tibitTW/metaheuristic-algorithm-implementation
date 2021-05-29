#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"

int P[POPSIZE][CHROMOSOME_LENGTH], P_tmp[POPSIZE][CHROMOSOME_LENGTH],
    fitness[POPSIZE];
int best_fitness = 0, best_chromosome[CHROMOSOME_LENGTH] = {0};

// generate random chromosome to entire population
void generatePopulation() {
    for (int chromo_i = 0; chromo_i < POPSIZE; chromo_i++) {
        for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
            P[chromo_i][i] = rand() * 2 / RAND_MAX;
        }
    }
}

// output best result in current iteration
void displayIterationResult(int iter_count, int tmp_max_fitness_index) {
    printf("###  Iteration count : %d  ###\n", iter_count);
    printf("Best chromosome in this iteration : [");
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        printf("%d", P[tmp_max_fitness_index][i]);
    }
    printf("]\n");
    printf("Best fitness in this iteration : %d\n\n",
           fitness[tmp_max_fitness_index]);

    printf("Best chromosome ever : [");
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        printf("%d", best_chromosome[i]);
    }
    printf("]\n");
    printf("Best fitness ever : %d\n\n", best_fitness);
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
}

// return fitness of chromosome
int calculateFitness(int *chromosome) {
    int fitness = 0;
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        fitness += chromosome[i];
    }
    return fitness;
}

// one point crossover for two chromosomes
void onePointCrossOver(int *chromo_1, int *chromo_2) {
    // point : the index to do crossover
    int point = rand() * 10 / RAND_MAX;

    int tmp;
    for (int i = point; i < CHROMOSOME_LENGTH; i++) {
        tmp = chromo_1[i];
        chromo_1[i] = chromo_2[i];
        chromo_2[i] = tmp;
    }
}

void mutation() {
    for (int chromo_i = 0; chromo_i < POPSIZE; chromo_i++) {
        if ((rand() / (float)RAND_MAX) > MUTATION_RATE) {
            int mutation_idx = rand() * CHROMOSOME_LENGTH / RAND_MAX;
            P[chromo_i][mutation_idx] ^= 1;
        }
    }
}

int main() {
    // make random seed
    srand(time(NULL));

    // generate a new random population
    generatePopulation();

    // iteration part
    for (int iter_count = 0; iter_count < ITERATION_COUNT; iter_count++) {
        // calculate fitness
        int tmp_max_fitness_index = 0;
        for (int i = 0; i < POPSIZE; i++) {
            fitness[i] = calculateFitness(P[i]);
            if (fitness[i] > fitness[tmp_max_fitness_index]) {
                tmp_max_fitness_index = i;
            }
        }

        if (fitness[tmp_max_fitness_index] > best_fitness) {
            best_fitness = fitness[tmp_max_fitness_index];
            for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
                best_chromosome[i] = P[tmp_max_fitness_index][i];
            }
        }

        // output current iteratoin count, best chromosome and its fitness
        displayIterationResult(iter_count + 1, tmp_max_fitness_index);

        // find the best solution, end the iteration early
        if (best_fitness == CHROMOSOME_LENGTH) {
            // break;
        }

        // DO SELECTION //
        // calculate sum of all fitness
        int fitness_sum = 0;
        for (int i = 0; i < POPSIZE; i++) {
            fitness_sum += fitness[i];
        }

        for (int new_chromo_i = 0; new_chromo_i < POPSIZE; new_chromo_i++) {
            int flag, selected_idx = 0, fitness_sum_currently = 0;
            flag = rand() * fitness_sum / RAND_MAX;
            while (fitness_sum_currently + fitness[selected_idx] < flag) {
                fitness_sum_currently += fitness[selected_idx];
                selected_idx++;
            }
            if (selected_idx == 20) {
                selected_idx--;
            }
            for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
                P_tmp[new_chromo_i][i] = P[selected_idx][i];
            }
        }

        // copy temp population to original population
        for (int chromo_i = 0; chromo_i < POPSIZE; chromo_i++) {
            for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
                P[chromo_i][i] = P_tmp[chromo_i][i];
            }
        }

        // crossover //
        int crossover_idx_tmp = -1;
        for (int chromo_i = 0; chromo_i < POPSIZE; chromo_i++) {
            if ((rand() / (float)RAND_MAX) > CROSSOVER_RATE) {
                if (crossover_idx_tmp == -1) {
                    crossover_idx_tmp = chromo_i;
                } else {
                    onePointCrossOver(P[crossover_idx_tmp], P[chromo_i]);
                    crossover_idx_tmp = -1;
                }
            }
        }

        // mutation //
        // if a chromosome mutations, one bit of this chromosome will change
        // (1 -> 0 or 0 -> 1)
        mutation();
    }

    // OUTPUT BEST RESULT

    return 0;
}