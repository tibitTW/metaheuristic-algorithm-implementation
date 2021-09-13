#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

#define CITY_DIM 10

using namespace std;
typedef vector<int> Chromo;

void OX(Chromo &c1, Chromo &c2) {
    Chromo new_c1, new_c2;

    int flag1 = rand() % CITY_DIM, flag2 = rand() % (CITY_DIM - 1);
    if (flag1 > flag2) {
        int tmp = flag1;
        flag1 = flag2;
        flag2 = tmp;
    } else {
        flag2 += 1;
    }
    flag1 = 3;
    flag2 = 5;

    bool is_in_substring;
    for (int i = flag2 + 1; i < CITY_DIM; i++) {
        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c1[i] == c2[fi]) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c1.push_back(c1[i]);
        }

        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c2[i] == c1[fi]) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c2.push_back(c2[i]);
        }
    }
    for (int i = 0; i < flag1; i++) {
        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c1[i] == c2[fi]) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c1.push_back(c1[i]);
        }
        is_in_substring = false;
        for (int fi = flag1; fi <= flag2; fi++) {
            if (c2[i] == c1[fi]) {
                is_in_substring = true;
                break;
            }
        }
        if (!is_in_substring) {
            new_c2.push_back(c2[i]);
        }
    }

    for (int i = flag1; i <= flag2; i++) {
        new_c1.push_back(c1[i]);
        new_c2.push_back(c2[i]);
    }
    for (int i = flag1; i <= flag2; i++) {
        new_c1.push_back(c2[i]);
        new_c2.push_back(c1[i]);
    }

    int ci = flag2 + 1;
    for (int i = 0; i < CITY_DIM; i++) {
        c1[ci] = new_c1[i];
        c2[ci] = new_c2[i];
        ci++;
        ci = (ci == CITY_DIM) ? 0 : ci;
    }
}
int main() {
    srand(time(NULL));
    Chromo c1{9, 8, 4, 5, 6, 7, 1, 3, 2, 0}, c2{8, 7, 1, 2, 3, 0, 9, 5, 4, 6};
    OX(c1, c2);

    for (auto cell : c1)
        cout << cell << " ";
    cout << endl;
    for (auto cell : c2)
        cout << cell << " ";
    cout << endl;

    return 0;
}