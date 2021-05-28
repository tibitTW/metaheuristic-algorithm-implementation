#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "gaconfig.h"


int P[POPSIZE][CHROMOSOME_LENGTH];
int P_tmp[POPSIZE][CHROMOSOME_LENGTH];
int fitness[POPSIZE];
int best_fitness = 0, best_chromosome[CHROMOSOME_LENGTH] = {0};

// generate random chromosome to entire population
int generatePopulation() {
    for (int chromo_i = 0; chromo_i < POPSIZE; chromo_i++) {
        for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
            P[chromo_i][i] = rand() * 2 / RAND_MAX;
        }
    }
}

// output best result in current iteration
void displayCurrentBestResult(int tmp_max_fitness_index) {
    printf("Current best chromosome : [ ");
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        printf("%d ", P[tmp_max_fitness_index][i]);
    }
    printf("]\n");
    printf("Current best fitness : %d\n", best_fitness);
    printf("\n------------------------------\n\n");
}

// return fitness of chromosome
int calculateFitness(int *chromosome) {
    int fitness = 0;
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        fitness += chromosome[i];
    }
    return fitness;
}

// do "one point crossover" for two chromosomes
void onePointCrossOver(int chromo_idx1, int chromo_idx2) {
    // point : the index to do crossover
    int point = rand() * 10 / RAND_MAX;

    int tmp;
    for (int i = point; i < CHROMOSOME_LENGTH; i++) {
        tmp = P[chromo_idx1][i];
        P[chromo_idx1][i] = P[chromo_idx2][i];
        P[chromo_idx2][i] = tmp;
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
            for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
                best_chromosome[i] = P[tmp_max_fitness_index][i];
                best_fitness = fitness[i];
            }
        }

        // output current iteratoin count, best chromosome and its fitness
        printf("Iteration count : %d\n", iter_count+1);
        displayCurrentBestResult(tmp_max_fitness_index);

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
            int selected_position = rand() * fitness_sum / RAND_MAX, selected_idx = 0;
            while (selected_position > 0) {
                selected_position -= fitness[selected_idx];
                selected_idx++;
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
        for (int i = 0; i < POPSIZE; i++) {
            if ((rand() / (float)RAND_MAX) > CROSSOVER_RATE) {
                if (crossover_idx_tmp == -1) {
                    crossover_idx_tmp = i;
                } else {
                    onePointCrossOver(crossover_idx_tmp, i);
                    crossover_idx_tmp = -1;
                }
            }
        }

        // mutation //
        // if a chromosome mutations, one bit of this chromosome will change
        // (1 -> 0 or 0 -> 1)
        for (int i = 0; i < POPSIZE; i++) {
            if ((rand() / (float)RAND_MAX) > MUTATION_RATE) {
                // do mutation
                int mutation_idx = rand() * CHROMOSOME_LENGTH / RAND_MAX;
                P[i][mutation_idx] ^= 1;
            }
        }
    }
    
    // OUTPUT BEST RESULT

    return 0;
}