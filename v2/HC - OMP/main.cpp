#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

bool load_argus(int argc, char *argv[], int &bs, int &im, int &runs, int &nb_type, char *output_file_path);
int ctoi(char *n_arr);
int get_fitness(int *arr, const int BIT_SIZE);
void update_neighbor(int *res_arr, int *arr, const int BIT_SIZE, int nb_type);
void update_solution(int *res_arr, int *arr, const int BIT_SIZE);
void HC(const int BIT_SIZE, const int ITER_MAX, const int NB_TYPE, int *result);
void write_result(FILE *f, int run, int *result, int ITER_MAX);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    char result_file_path[100] = "result.csv";

    // load arguments
    int bs_tmp = 100, im_tmp = 200, runs_tmp = 51, nb_type_tmp = 0;
    bool is_help = load_argus(argc, argv, bs_tmp, im_tmp, runs_tmp, nb_type_tmp, result_file_path);
    if (is_help) {
        cout << "usage: main.exe [options]\n"
                "example: main.exe -b 50 -i 100 -n 0\n"
                "\n"
                "options:\n"
                "-b, -bit-size\t\tbit size, default value = 100\n"
                "-i, -iter-max\t\tmax iteration of HC algorithm, default value is 200\n"
                "-r, -run\t\ttimes of HC algorithm runs, default value is 51\n"
                "-n, -neighbor-type\tneighbor type in HC algorithm, default value is 0. Options : \"0\", \"numeric\", \"1\", "
                "\"random_bit\" (0 equals to numeric and 1 equals to random_bit)\n"
                "-o, -output-path\tthe path of CSV file records result, default path is \"result.csv\"";
        return 0;
    }
    const int BIT_SIZE = bs_tmp, ITER_MAX = im_tmp, RUNS = runs_tmp, NB_TYPE = nb_type_tmp;

    FILE *result_file;
    result_file = fopen(result_file_path, "w");

    // write column names
    // fprintf(result_file, "runid,");
    // for (int iter = 0; iter <= ITER_MAX; iter++) {
    //     fprintf(result_file, "%d", iter);
    //     if (iter != ITER_MAX) {
    //         fprintf(result_file, ",");
    //     }
    // }
    // fprintf(result_file, "\n");

    int *result;
    result = new int(ITER_MAX + 1);
    for (int run = 1; run <= RUNS; run++) {
        // call HC repeatly
        HC(BIT_SIZE, ITER_MAX, NB_TYPE, result);
        write_result(result_file, run, result, ITER_MAX);
    }

    fclose(result_file);

    return 0;
}

bool load_argus(int argc, char *argv[], int &bs, int &im, int &runs, int &nb_type, char *output_file_path) {
    if (strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-h") == 0) {
        return true;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "-bit-size") == 0) {
            bs = ctoi(argv[++i]);
        } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-iter-cnt") == 0) {
            im = ctoi(argv[++i]);
        } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-run") == 0) {
            runs = ctoi(argv[++i]);
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-neighbor-type") == 0) {
            if (strcmp(argv[i + 1], "numeric") == 0 || strcmp(argv[i + 1], "0") == 0) {
                nb_type = 0;
            } else if (strcmp(argv[i + 1], "random_bit") == 0 || strcmp(argv[i + 1], "1") == 0) {
                nb_type = 1;
            }
            i++;
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "-output-file") == 0) {
            strcpy(output_file_path, argv[++i]);
        }
    }

    return false;
}
// turn char[] to int;
int ctoi(char *n_arr) {
    int i = 0, res = 0;
    while (n_arr[i] != '\0') {
        res *= 10;
        res += n_arr[i] - '0';
        i++;
    }

    return res;
}
int get_fitness(int *arr, const int BIT_SIZE) {
    int res = 0;
    for (int i = 0; i < BIT_SIZE; i++) {
        res += arr[i];
    }
    return res;
}
void update_neighbor(int *res_arr, int *arr, const int BIT_SIZE, int nb_type) {
    if (nb_type == 0) {
        int rd = rand() % 2;
        if (rd == 0) {
            int bi = BIT_SIZE - 1;
            while (!arr[bi]) {
                res_arr[bi] = 1;
                bi--;
            }
            res_arr[bi] = 0;
            while (bi) {
                res_arr[bi - 1] = arr[bi - 1];
                bi--;
            }
        } else {
            int hold = 1;
            for (int bi = BIT_SIZE - 1; bi >= 0; bi--) {
                res_arr[bi] = arr[bi];
                if (res_arr[bi]) {
                    if (hold) {
                        res_arr[bi] = 0;
                    }
                } else {
                    if (hold) {
                        res_arr[bi] = 1;
                        hold = 0;
                    }
                }
            }
        }
    } else if (nb_type == 1) {
        int ri = rand() % BIT_SIZE;
        int bi = 0;
        while (bi != ri) {
            res_arr[bi] = arr[bi];
            bi++;
        }
        res_arr[bi] = arr[bi] == 0 ? 1 : 0;
        bi++;
        while (bi < BIT_SIZE) {
            res_arr[bi] = arr[bi];
            bi++;
        }
    }
}
void update_solution(int *res_arr, int *arr, const int BIT_SIZE) {
    for (int bi = 0; bi < BIT_SIZE; bi++) {
        res_arr[bi] = arr[bi];
    }
}
void HC(const int BIT_SIZE, const int ITER_MAX, const int NB_TYPE, int *result) {
    // initialize
    int *sol, *next_sol, fitness, nb_fitness;

    sol = (int *)malloc(sizeof(int) * BIT_SIZE);
    // sol = new int(BIT_SIZE + 1);
    next_sol = (int *)malloc(sizeof(int) * BIT_SIZE);
    // next_sol = new int(BIT_SIZE + 1);
    for (int bi = 0; bi < BIT_SIZE; bi++) {
        sol[bi] = rand() % 2;
    }
    fitness = get_fitness(sol, BIT_SIZE);
    result[0] = fitness;

    // iteration
    for (int iter = 0; iter < ITER_MAX; iter++) {
        update_neighbor(next_sol, sol, BIT_SIZE, NB_TYPE);
        nb_fitness = get_fitness(next_sol, BIT_SIZE);
        if (nb_fitness >= fitness) {
            update_solution(sol, next_sol, BIT_SIZE);
            fitness = nb_fitness;
        }
        result[iter + 1] = fitness;
    }
}
void write_result(FILE *f, int run, int *result, int ITER_MAX) {
    fprintf(f, "%d,", run);
    for (int iter = 0; iter <= ITER_MAX; iter++) {
        fprintf(f, "%d", result[iter]);
        if (iter != ITER_MAX) {
            fprintf(f, ",");
        }
    }
    fprintf(f, "\n");
}