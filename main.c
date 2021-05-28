#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPSIZE 10  // pop size should be even
#define CHROMOSOME_LENGTH 10
#define ITERATION_COUNT 100

int P[POPSIZE][CHROMOSOME_LENGTH];

int generatePopulation() {
    for (int chromo_i = 0; chromo_i < POPSIZE; chromo_i++) {
        for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
            P[chromo_i][i] = rand() * 2 / RAND_MAX;
        }
    }
}

int calculateFitness(int *chromosome) {
    int fitness = 0;
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        fitness += chromosome[i];
    }
    return fitness;
}

void onePointCrossOver(int *chromosomeA, int *chromosomeB) {
    // point : the index to do crossover
    int point = rand() * 10 / RAND_MAX;

    int tmp;
    for (int i = point; i < CHROMOSOME_LENGTH; i++) {
        tmp = chromosomeA[i];
        chromosomeA[i] = chromosomeB[i];
        chromosomeB[i] = tmp;
    }
}


int main() {
    srand(time(NULL));

    // generate population
    generatePopulation();

    // print out all chromosomes
    for (int chromo_i = 0; chromo_i < POPSIZE; chromo_i++) {
        printf("Chromosome %2d : [ ", chromo_i+1);
        for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
            printf("%d ", P[chromo_i][i]);
        }
        printf("]\n");
    }

    // iteration part
    for (int iteration_i = 0; iteration_i < ITERATION_COUNT; iteration_i++) {
        // CALCULATE FITNESS 
        // DO SELECTION
        // DO CROSSOVER
        // DO MUTATION 
    }
    
    // OUTPUT BEST RESULT

    return 0;
}