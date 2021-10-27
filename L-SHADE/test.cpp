#include "de.hpp"

#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

random_device rd;
default_random_engine generator;

void print_v(vector<int> v) {
    for (auto i : v)
        cout << i << " ";
    cout << endl;
}

void quick_sort(vector<int> &v, int left, int right) {
    if (right - left < 2)
        return;

    uniform_int_distribution<int> int_dt(left, right);

    int r1 = int_dt(generator), r2 = int_dt(generator), r3 = int_dt(generator), rnd;

    if (v[r1] > v[r2]) {
        if (v[r2] > v[r3])
            rnd = r2;
        else
            rnd = v[r1] > v[r3] ? r3 : r1;
    } else {
        if (v[r1] > v[r3])
            rnd = r1;
        else
            rnd = v[r2] > v[r3] ? r3 : r2;
    }

    printf("v[r1]: %2d, v[r2]: %2d, v[r3]: %2d, v[rnd]: %2d\n", v[r1], v[r2], v[r3], v[rnd]);
    printf("left: %d, right: %d\n", left, right);

    int num_tmp, l = left, r = right;
    while (l < r) {
        while (v[l] < v[rnd])
            l++;
        while (v[rnd] < v[r])
            r--;

        print_v(v);
        printf("swap v[%d]: %d and v[%d]: %d\n", l, v[l], r, v[r]);
        print_v(v);
        printf("---------------------------------\n");

        // swap
        num_tmp = v[l];
        v[l] = v[r];
        v[r] = num_tmp;
    }
    cout << endl << endl;

    num_tmp = v[l];
    v[l] = v[rnd];
    v[rnd] = num_tmp;

    quick_sort(v, left, l - 1);
    quick_sort(v, r, right);
}

int main() {
    vector<int> v1 = {19, 10, 8, 5, 6, 15, 12, 9, 3, 16, 11, 17, 2, 18, 4, 1, 13, 20, 7, 14};
    quick_sort(v1, 0, v1.size() - 1);

    for (auto i : v1)
        cout << i << " ";

    // DE de(100, 1000, 10, -30.0, 30.0);
    // de.test();
    // de.run();

    return 0;
}