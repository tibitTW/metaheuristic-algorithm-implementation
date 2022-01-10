#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <random>
#include <stdlib.h>
#include <vector>

using namespace std;

// data structure
typedef vector<int> i1d;
typedef vector<i1d> i2d;
typedef vector<double> d1d;
typedef vector<d1d> d2d;

// * output experiment details
ofstream fout;

class aco {
  private:
    // random number generator
    random_device rd;
    mt19937 mt{rd()};
    uniform_real_distribution<double> dist{0.0, 1.0};
    normal_distribution<double> ndist{5.0, 1.0};

    int num_city_dim, num_ant_pop, num_max_iter, num_phero_ctrl_factor, num_dis_ctrl_factor,
        num_2opt_amount;
    double num_phero_ant_carried, num_evaporation_factor, num_min_phero_amount, num_pbest;
    // char *filename;
    double q0 = 0.5;

    i2d city_location;
    d2d city_dist_matrix, phero_matrix, exc_val_matrix;
    d1d path_length;
    i2d paths, paths_archive;
    int ants_current_city;

    // temp vectors
    i1d path, ants_visited_city;
    d1d exc_val_table, chosen_rate_table, chosen_rate_table_acc;

    /* ----------------- functions ----------------- */
    // initialization
    void load_city_location();
    double get_2city_distance(i1d c1, i1d c2);
    void init_city_dist_matrix();
    void init_phero_matrix();
    // during iteration
    i1d get_path();
    i1d get_path_v2();
    double get_path_len(i1d path);
    double calcu_exc_val(double tau, double eta);
    void update_exc_val_matrix();
    void update_phero_matrix();
    void update_phero_matrix_v2();
    i1d get_2opt_path(i1d path);
    void update_path_archive();
    // quick sort
    int partition(int front, int end);
    void quick_sort(int front, int end);

  public:
    aco(int num_city_dim, int num_ant_pop, int num_max_iter, double num_phero_ant_carried,
        int num_phero_ctrl_factor, int num_dist_ctrl_factor, double num_evaporation_factor,
        double num_min_phero_amount, int num_2opt_amount, double num_pbest);
    d1d run();
};

aco::aco(int num_city_dim, int num_ant_pop, int num_max_iter, double num_phero_ant_carried,
         int num_phero_ctrl_factor, int num_dist_ctrl_factor, double num_evaporation_factor,
         double num_min_phero_amount, int num_2opt_amount, double num_pbest) {
    this->num_city_dim = num_city_dim;
    this->num_ant_pop = num_ant_pop;
    this->num_max_iter = num_max_iter;
    this->num_phero_ant_carried = num_phero_ant_carried;
    this->num_phero_ctrl_factor = num_phero_ctrl_factor;
    this->num_dis_ctrl_factor = num_dist_ctrl_factor;
    this->num_evaporation_factor = num_evaporation_factor;
    this->num_min_phero_amount = num_min_phero_amount;
    this->num_2opt_amount = num_2opt_amount;
    this->num_pbest = num_pbest;

    load_city_location();
    init_city_dist_matrix();

    // ✅ assign pheromone matrix
    phero_matrix.assign(num_city_dim, d1d(num_city_dim, 0.0));
    exc_val_matrix.assign(num_city_dim, d1d(num_city_dim, 0.0));

    paths.assign(num_ant_pop, i1d(num_city_dim));
    path_length.assign(num_ant_pop, 0);
}
/* ------------------ private ------------------ */
void aco::load_city_location() {
    city_location.assign(num_city_dim, i1d(2));
    int tmp, c1, c2;
    ifstream fin("./dataset/eil51.txt");
    for (int i = 0; i < num_city_dim; i++) {
        fin >> tmp >> c1 >> c2;
        city_location.at(i).at(0) = c1;
        city_location.at(i).at(1) = c2;
    }
}
void aco::init_city_dist_matrix() {
    city_dist_matrix.assign(num_city_dim, d1d(num_city_dim, 0));
    for (int i = 0; i < num_city_dim; i++)
        for (int j = i + 1; j < num_city_dim; j++)
            city_dist_matrix.at(i).at(j) = city_dist_matrix.at(j).at(i) =
                get_2city_distance(city_location.at(i), city_location.at(j));
}
double aco::get_2city_distance(i1d c1, i1d c2) {
    return sqrt(pow(c1[0] - c2[0], 2) + pow(c1[1] - c2[1], 2));
}
void aco::init_phero_matrix() {
    phero_matrix.assign(num_city_dim, d1d(num_city_dim, num_min_phero_amount));
    for (int i = 0; i < num_city_dim; i++)
        phero_matrix.at(i).at(i) = 0;
}
double aco::calcu_exc_val(double tau, double eta) {
    return pow(tau, num_phero_ctrl_factor) * pow(1 / eta, num_dis_ctrl_factor);
}
void aco::update_exc_val_matrix() {
    double tau, eta;
    for (int i = 0; i < num_city_dim; i++) {
        for (int j = i + 1; j < num_city_dim; j++) {
            tau = phero_matrix.at(i).at(j);
            eta = city_dist_matrix.at(i).at(j);
            exc_val_matrix.at(i).at(j) = exc_val_matrix.at(j).at(i) = calcu_exc_val(tau, eta);
        }
    }
}
i1d aco::get_path() {
    // clear temp vectors content
    path.clear();
    ants_visited_city.assign(num_city_dim, 0);
    exc_val_table.assign(num_city_dim, 0);
    chosen_rate_table.assign(num_city_dim, 0);
    chosen_rate_table_acc.assign(num_city_dim, 0);

    int current_city = dist(mt) * num_city_dim, c_tmp;
    double exc_val_sum, chosen_rate_sum;
    path.push_back(current_city);
    ants_visited_city.at(current_city) = 1;

    for (int i = 0; i < num_city_dim - 1; i++) {
        exc_val_sum = 0;
        chosen_rate_sum = 0;

        // update exc_val_table
        for (int j = 0; j < num_city_dim; j++)
            if (!ants_visited_city.at(j)) {
                exc_val_table.at(j) = exc_val_matrix.at(current_city).at(j);
                exc_val_sum += exc_val_table.at(j);
            }

        for (int j = 0; j < num_city_dim; j++)
            if (!ants_visited_city.at(j))
                chosen_rate_table.at(j) = exc_val_table.at(j) / exc_val_sum;
            else
                chosen_rate_table.at(j) = 0;

        for (int j = 0; j < num_city_dim; j++) {
            if (!ants_visited_city.at(j)) {
                chosen_rate_sum += chosen_rate_table.at(j);
                chosen_rate_table_acc.at(j) = chosen_rate_sum;
            } else
                chosen_rate_table_acc.at(j) = 0;
        }

        // find next city
        double r = dist(mt);
        int ci = 0;
        while (r > chosen_rate_table_acc.at(ci))
            ci++;

        current_city = ci;
        ants_visited_city.at(current_city) = 1;
        path.push_back(current_city);
    }

    return path;
}
i1d aco::get_path_v2() {
    // clear temp vectors content

    path.clear();
    ants_visited_city.assign(num_city_dim, 0);
    exc_val_table.assign(num_city_dim, 0);
    chosen_rate_table.assign(num_city_dim, 0);
    chosen_rate_table_acc.assign(num_city_dim, 0);

    // choose random path from archive
    int pi = dist(mt) * paths_archive.size();
    // choose random piece and put in path
    int length = ndist(mt), ci = dist(mt) * num_city_dim;

    int i = ci;
    while (i < length) {
        path.push_back(paths_archive.at(pi).at(i));
        ants_visited_city.at(path.back()) = 1;
        i++;
    }

    // update 剩下的 path
    int current_city = path.back(), c_tmp;
    double exc_val_sum, chosen_rate_sum;

    while (path.size() != num_city_dim) {
        exc_val_sum = 0;
        chosen_rate_sum = 0;

        // update exc_val_table
        for (int j = 0; j < num_city_dim; j++)
            if (!ants_visited_city.at(j)) {
                exc_val_table.at(j) = exc_val_matrix.at(current_city).at(j);
                exc_val_sum += exc_val_table.at(j);
            }

        for (int j = 0; j < num_city_dim; j++)
            if (!ants_visited_city.at(j))
                chosen_rate_table.at(j) = exc_val_table.at(j) / exc_val_sum;
            else
                chosen_rate_table.at(j) = 0;

        for (int j = 0; j < num_city_dim; j++) {
            if (!ants_visited_city.at(j)) {
                chosen_rate_sum += chosen_rate_table.at(j);
                chosen_rate_table_acc.at(j) = chosen_rate_sum;
            } else
                chosen_rate_table_acc.at(j) = 0;
        }

        // find next city
        double r = dist(mt);
        int ci = 0;
        while (r > chosen_rate_table_acc.at(ci))
            ci++;

        current_city = ci;
        ants_visited_city.at(current_city) = 1;
        path.push_back(current_city);
    }

    return path;
}
double aco::get_path_len(i1d path) {
    double length = 0;
    int c1, c2;
    for (int i = 0; i < num_city_dim - 1; i++) {
        c1 = path.at(i), c2 = path.at(i + 1);
        length += city_dist_matrix.at(c1).at(c2);
    }
    c1 = path.at(num_city_dim - 1), c2 = path.at(0);
    length += city_dist_matrix.at(c1).at(c2);

    return length;
}
void aco::update_phero_matrix() {
    // 1. reduce
    for (int i = 0; i < num_city_dim; i++) {
        for (int j = i + 1; j < num_city_dim; j++) {
            if (i != j) {
                phero_matrix.at(i).at(j) *= (1 - num_evaporation_factor);
                phero_matrix.at(j).at(i) = phero_matrix.at(i).at(j);
                if (phero_matrix.at(i).at(j) < num_min_phero_amount)
                    phero_matrix.at(i).at(j) = num_min_phero_amount;
                phero_matrix.at(j).at(i) = phero_matrix.at(i).at(j);
            }
        }
    }
    // 2. add new phero
    int c1, c2;
    for (int ai = 0; ai < num_ant_pop; ai++) {
        for (int ci = 0; ci < num_city_dim - 1; ci++) {
            c1 = paths.at(ai).at(ci);
            c2 = paths.at(ai).at(ci + 1);
            phero_matrix.at(c1).at(c2) += path_length.at(ai) / city_dist_matrix.at(c1).at(c2);
            phero_matrix.at(c2).at(c1) = phero_matrix.at(c1).at(c2);
        }
        c1 = paths.at(ai).at(num_city_dim - 1);
        c2 = paths.at(ai).at(0);
        phero_matrix.at(c1).at(c2) += path_length.at(ai) / city_dist_matrix.at(c1).at(c2);
        phero_matrix.at(c2).at(c1) = phero_matrix.at(c1).at(c2);
    }
}
void aco::update_phero_matrix_v2() {
    // 1. reduce
    for (int i = 0; i < num_city_dim; i++) {
        for (int j = i + 1; j < num_city_dim; j++) {
            if (i != j) {
                phero_matrix.at(i).at(j) *= (1 - num_evaporation_factor);
                phero_matrix.at(j).at(i) = phero_matrix.at(i).at(j);
                if (phero_matrix.at(i).at(j) < num_min_phero_amount)
                    phero_matrix.at(i).at(j) = num_min_phero_amount;
                phero_matrix.at(j).at(i) = phero_matrix.at(i).at(j);
            }
        }
    }
    // 2. add new phero
    int c1, c2;
    for (int ai = 0; ai < num_ant_pop * num_pbest; ai++) {
        for (int ci = 0; ci < num_city_dim - 1; ci++) {
            c1 = paths.at(ai).at(ci);
            c2 = paths.at(ai).at(ci + 1);
            phero_matrix.at(c1).at(c2) += path_length.at(ai) / city_dist_matrix.at(c1).at(c2);
            phero_matrix.at(c2).at(c1) = phero_matrix.at(c1).at(c2);
        }
        c1 = paths.at(ai).at(num_city_dim - 1);
        c2 = paths.at(ai).at(0);
        phero_matrix.at(c1).at(c2) += path_length.at(ai) / city_dist_matrix.at(c1).at(c2);
        phero_matrix.at(c2).at(c1) = phero_matrix.at(c1).at(c2);
    }
}
i1d aco::get_2opt_path(i1d path) {
    i1d new_path = path;
    int rdn_city_idx1, rdn_city_idx2;
    rdn_city_idx1 = dist(mt) * num_city_dim;
    do
        rdn_city_idx2 = dist(mt) * num_city_dim;
    while (rdn_city_idx1 == rdn_city_idx2);

    // swap
    if (rdn_city_idx2 < rdn_city_idx1)
        swap(rdn_city_idx1, rdn_city_idx2);

    while (rdn_city_idx1 < rdn_city_idx2) {
        int tmp = new_path.at(rdn_city_idx1);
        new_path.at(rdn_city_idx1) = new_path.at(rdn_city_idx2);
        new_path.at(rdn_city_idx2) = tmp;
        rdn_city_idx1++;
        rdn_city_idx2--;
    }

    return new_path;
}
int aco::partition(int front, int end) {
    double pivot = path_length.at(end);
    int i = front - 1;
    for (int j = front; j < end; j++) {
        if (path_length.at(j) < pivot) {
            i++;
            swap(path_length.at(i), path_length.at(j));
            swap(paths.at(i), paths.at(j));
        }
    }
    i++;
    swap(path_length.at(i), path_length.at(end));
    swap(paths.at(i), paths.at(end));
    return i;
}
void aco::quick_sort(int front, int end) {
    if (front >= end)
        return;
    int pivot_idx = partition(front, end);
    quick_sort(front, pivot_idx - 1);
    quick_sort(pivot_idx + 1, end);
}
void aco::update_path_archive() {
    paths_archive.clear();
    for (int i = 0; i < num_ant_pop * num_pbest; i++)
        paths_archive.push_back(paths.at(i));
}

/* ------------------ public ------------------ */
d1d aco::run() {
    d1d result;
    double best_result = 1e10;
    i1d best_path;

    double tmp_2opt_path_len;
    i1d tmp_2opt_path;

    // initialize pheromone matrix
    init_phero_matrix();
    update_exc_val_matrix();

    for (int ii = 0; ii < num_max_iter; ii++) {
        // ========== generate path for each ant ========== //
        for (int ai = 0; ai < num_ant_pop; ai++) {
            // generate a path
            if (paths_archive.size() != 0)
                paths.at(ai) = get_path_v2();
            else
                paths.at(ai) = get_path();

            // paths.at(ai) = get_path();

            // calculate path length
            path_length.at(ai) = get_path_len(paths.at(ai));

            // local search 2opt
            // if (ii >= int(num_max_iter / 2)) {
            for (int li = 0; li < num_2opt_amount; li++) {
                tmp_2opt_path = get_2opt_path(paths.at(ai));

                tmp_2opt_path_len = get_path_len(tmp_2opt_path);
                if (tmp_2opt_path_len < path_length.at(ai)) {
                    paths.at(ai) = tmp_2opt_path;
                    path_length.at(ai) = tmp_2opt_path_len;
                }
            }
            // }
        }

        // sort solution by path length
        quick_sort(0, num_ant_pop - 1);

        update_path_archive();

        for (int ai = 0; ai < num_ant_pop; ai++) {
            // update best solution
            if (path_length.at(ai) < best_result)
                best_result = path_length.at(ai);
            best_path = paths.at(ai);
        }

        update_phero_matrix_v2();
        update_exc_val_matrix();

        result.push_back(best_result);

        // ***************** debug ***************** //

        // fout.open("./path.txt", ios::app);
        // for (int ai =4 0; ai < num_ant_pop; ai++) {
        //     for (int ci = 0; ci < num_city_dim; ci++)
        //         fout << paths.at(ai).at(ci) << " ";
        //     fout << endl;
        // }
        // fout.close();

        // fout.open("./phero.txt", ios::app);
        // for (int i = 0; i < num_city_dim; i++) {
        //     for (int j = 0; j < num_city_dim; j++)
        //         fout << setprecision(6) << phero_matrix.at(i).at(j) << " ";
        // }
        // fout << endl;
        // fout.close();
        // ***************************************** //
    }

    // local search 2opt
    for (int ai = 0; ai < num_ant_pop; ai++) {
        for (int li = 0; li < 100; li++) {
            tmp_2opt_path = get_2opt_path(paths.at(ai));

            tmp_2opt_path_len = get_path_len(tmp_2opt_path);
            if (tmp_2opt_path_len < path_length.at(ai)) {
                paths.at(ai) = tmp_2opt_path;
                path_length.at(ai) = tmp_2opt_path_len;
            }
        }
        // update best solution
        if (path_length.at(ai) < best_result)
            best_result = path_length.at(ai);
        best_path = paths.at(ai);
    }

    fout.open("./path.txt", ios::out | ios::trunc);
    fout << "path " << result.back() << " : ";
    for (int i = 0; i < num_city_dim; i++)
        fout << best_path.at(i) << " ";
    fout << endl;
    fout.close();

    return result;
}
