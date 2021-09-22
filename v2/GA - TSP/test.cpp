#include <cstdlib>
#include <iostream>
#include <math.h>
#include <set>
#include <time.h>
#include <vector>

#define CITY_DIM 9

using namespace std;
typedef vector<int> Chromo;

void OX(Chromo &c1, Chromo &c2) {
    Chromo new_c1, new_c2;
    // set start and stop point of substring
    int flag1 = rand() % CITY_DIM, flag2 = rand() % (CITY_DIM - 1);
    if (flag1 > flag2) {
        int tmp = flag1;
        flag1 = flag2;
        flag2 = tmp;
    } else {
        flag2 += 1;
    }

    set<int> s1, s2;
    for (int i = flag1; i <= flag2; i++) {
        s1.insert(c1.at(i));
        s2.insert(c2.at(i));
    }

    for (int i = 0; i < CITY_DIM; i++) {

        if (!s2.count(c1.at(i))) {
            new_c2.push_back(c1.at(i));
        }
        if (new_c2.size() == flag1) {
            for (int i2 = flag1; i2 <= flag2; i2++) {
                new_c2.push_back(c2.at(i2));
            }
        }

        if (!s1.count(c2.at(i))) {
            new_c1.push_back(c2.at(i));
        }
        if (new_c1.size() == flag1) {
            for (int i2 = flag1; i2 <= flag2; i2++) {
                new_c1.push_back(c1.at(i2));
            }
        }
    }
}

int main() {
    srand(time(NULL));
    Chromo c1{1, 2, 3, 4, 5, 6, 7, 8, 9}, c2{5, 7, 4, 9, 1, 3, 6, 2, 8};
    OX(c1, c2);

    return 0;
}